__libc_wait (__WAIT_STATUS_DEFN stat_loc)
{
  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (wait4, 4, WAIT_ANY, stat_loc, 0,
			   (struct rusage *) NULL);

  int oldtype = LIBC_CANCEL_ASYNC ();

  pid_t result = INLINE_SYSCALL (wait4, 4, WAIT_ANY, stat_loc, 0,
				 (struct rusage *) NULL);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
