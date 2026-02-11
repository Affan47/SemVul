epoll_pwait (int epfd, struct epoll_event *events,
		 int maxevents, int timeout,
		 const sigset_t *set)
{
  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (epoll_pwait, 6, epfd, events, maxevents, timeout,
			   set, _NSIG / 8);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int result = INLINE_SYSCALL (epoll_pwait, 6, epfd, events, maxevents,
			       timeout, set, _NSIG / 8);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
