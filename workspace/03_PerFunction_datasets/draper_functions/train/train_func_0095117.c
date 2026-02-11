__sched_getaffinity_new (pid_t pid, size_t cpusetsize, cpu_set_t *cpuset)
{
  int res = INLINE_SYSCALL (sched_getaffinity, 3, pid,
			    MIN (INT_MAX, cpusetsize), cpuset);
  if (res != -1)
    {

      memset ((char *) cpuset + res, '\0', cpusetsize - res);

      res = 0;
    }
  return res;
}
