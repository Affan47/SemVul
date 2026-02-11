sched_getcpu (void)
{
#ifdef __NR_getcpu
  unsigned int cpu;
  int r = INLINE_SYSCALL (getcpu, 3, &cpu, NULL, NULL);

  return r == -1 ? r : cpu;
#else
  __set_errno (ENOSYS);
  return -1;
#endif
}
