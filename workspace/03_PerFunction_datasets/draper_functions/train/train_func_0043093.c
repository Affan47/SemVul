GetCPUTimeMicroSeconds(Timer::CPUTime* cpu_time) const {
#if !defined(_WIN32) && !defined(_WIN64)
  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage)) {
    TRACE_ERR("Error occurred: getrusage().\n");
    exit(1);
  }
  cpu_time->user_time = GetMicroSeconds(usage.ru_utime);
  cpu_time->sys_time = GetMicroSeconds(usage.ru_stime);
#else


#endif
}
