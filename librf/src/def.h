﻿#pragma once

#define RESUMEF_LIB_INCLUDE	1

//#include <yvals.h>
#include <atomic>
#include <chrono>
#include <vector>
#include <deque>
#include <mutex>
#include <map>
#include <list>
#include <unordered_map>
#include <functional>
#include <optional>
#include <thread>

#include <assert.h>

#include <experimental/coroutine>
//#include <experimental/generator>

#define LIB_RESUMEF_VERSION 200101 // 2.1.1

namespace resumef
{
	struct scheduler_t;

	template<class _Ty = void>
	struct future_t;
	using future_vt [[deprecated]] = future_t<>;

	template <typename _Ty = std::nullptr_t, typename _Alloc = std::allocator<char>>
	struct generator_t;

	template<class _Ty = void>
	struct promise_t;

	template<class _Ty = void>
	struct awaitable_t;

	//获得当前线程下的调度器
	scheduler_t* this_scheduler();

	template<typename _PromiseT = void>
	using coroutine_handle = std::experimental::coroutine_handle<_PromiseT>;

	struct state_base_t;

	template<class... _Mutexes>
	using scoped_lock = std::scoped_lock<_Mutexes...>;
}

#if RESUMEF_DEBUG_COUNTER
extern std::mutex g_resumef_cout_mutex;
extern std::atomic<intptr_t> g_resumef_state_count;
extern std::atomic<intptr_t> g_resumef_task_count;
extern std::atomic<intptr_t> g_resumef_evtctx_count;
extern std::atomic<intptr_t> g_resumef_state_id;
#endif

namespace resumef
{
	template<class T>
	struct remove_cvref
	{
		typedef std::remove_cv_t<std::remove_reference_t<T>> type;
	};
	template<class T>
	using remove_cvref_t = typename remove_cvref<T>::type;


	template<class _Ty>
	constexpr size_t _Align_size()
	{
		const size_t _ALIGN_REQ = sizeof(void*) * 2;
		return std::is_empty_v<_Ty> ? 0 :
			(sizeof(_Ty) + _ALIGN_REQ - 1) & ~(_ALIGN_REQ - 1);
	}
}

#if defined(RESUMEF_DLL_EXPORT)
#	define RF_API __declspec(dllexport)
#elif defined(RESUMEF_DLL_IMPORT)
#	define RF_API __declspec(dllimport)
#else
#	define RF_API
#endif

#include "exception.inl"
#include "type_traits.inl"

#define co_yield_void co_yield nullptr
#define co_return_void co_return nullptr
