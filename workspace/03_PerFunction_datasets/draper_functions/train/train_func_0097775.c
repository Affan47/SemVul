__arch_prctl (int code, uintptr_t *addr)
{
  int res;
  uint64_t addr64;
  void *prctl_arg = addr;

  switch (code)
    {
    case ARCH_GET_FS:
    case ARCH_GET_GS:
      prctl_arg = &addr64;
      break;
    }

  res = INLINE_SYSCALL (arch_prctl, 2, code, prctl_arg);
  if (res == 0)
    switch (code)
      {
      case ARCH_GET_FS:
      case ARCH_GET_GS:

	if ((uintptr_t) addr64 != addr64)
	  {
	    __set_errno (EOVERFLOW);
	    return -1;
	  }
	*addr = (uintptr_t) addr64;
	break;
      }

  return res;
}
