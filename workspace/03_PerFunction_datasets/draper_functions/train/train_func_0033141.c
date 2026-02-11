prlimit (__pid_t pid, enum __rlimit_resource resource,
	 const struct rlimit *new_rlimit, struct rlimit *old_rlimit)
{
  struct rlimit64 new_rlimit64_mem;
  struct rlimit64 *new_rlimit64 = NULL;
  struct rlimit64 old_rlimit64_mem;
  struct rlimit64 *old_rlimit64 = (old_rlimit != NULL
				   ? &old_rlimit64_mem : NULL);

  if (new_rlimit != NULL)
    {
      if (new_rlimit->rlim_cur == RLIM_INFINITY)
	new_rlimit64_mem.rlim_cur = RLIM64_INFINITY;
      else
	new_rlimit64_mem.rlim_cur = new_rlimit->rlim_cur;
      if (new_rlimit->rlim_max == RLIM_INFINITY)
	new_rlimit64_mem.rlim_max = RLIM64_INFINITY;
      else
	new_rlimit64_mem.rlim_max = new_rlimit->rlim_max;
      new_rlimit64 = &new_rlimit64_mem;
    }

  int res = INLINE_SYSCALL (prlimit64, 4, pid, resource, new_rlimit64,
			    old_rlimit64);

  if (res == 0 && old_rlimit != NULL)
    {


      old_rlimit->rlim_cur = old_rlimit64_mem.rlim_cur;
      if (old_rlimit->rlim_cur != old_rlimit64_mem.rlim_cur)
	{
	  if (new_rlimit == NULL)
	    {
	      __set_errno (EOVERFLOW);
	      return -1;
	    }
	  old_rlimit->rlim_cur = RLIM_INFINITY;
	}
      old_rlimit->rlim_max = old_rlimit64_mem.rlim_max;
      if (old_rlimit->rlim_max != old_rlimit64_mem.rlim_max)
	{
	  if (new_rlimit == NULL)
	    {
	      __set_errno (EOVERFLOW);
	      return -1;
	    }
	  old_rlimit->rlim_max = RLIM_INFINITY;
	}
    }

  return res;
}
