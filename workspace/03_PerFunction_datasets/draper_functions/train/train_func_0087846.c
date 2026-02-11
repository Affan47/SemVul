hwloc_fallback_nbprocessors(struct hwloc_topology *topology) {
  int n;
#if HAVE_DECL__SC_NPROCESSORS_ONLN
  n = sysconf(_SC_NPROCESSORS_ONLN);
#elif HAVE_DECL__SC_NPROC_ONLN
  n = sysconf(_SC_NPROC_ONLN);
#elif HAVE_DECL__SC_NPROCESSORS_CONF
  n = sysconf(_SC_NPROCESSORS_CONF);
#elif HAVE_DECL__SC_NPROC_CONF
  n = sysconf(_SC_NPROC_CONF);
#elif defined(HAVE_HOST_INFO) && HAVE_HOST_INFO
  struct host_basic_info info;
  mach_msg_type_number_t count = HOST_BASIC_INFO_COUNT;
  host_info(mach_host_self(), HOST_BASIC_INFO, (integer_t*) &info, &count);
  n = info.avail_cpus;
#elif defined(HAVE_SYSCTLBYNAME)
  int64_t nn;
  if (hwloc_get_sysctlbyname("hw.ncpu", &nn))
    nn = -1;
  n = nn;
#elif defined(HAVE_SYSCTL) && HAVE_DECL_CTL_HW && HAVE_DECL_HW_NCPU
  static int name[2] = {CTL_HW, HW_NPCU};
  if (hwloc_get_sysctl(name, sizeof(name)/sizeof(*name)), &n)
    n = -1;
#elif defined(HWLOC_WIN_SYS)
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);
  n = sysinfo.dwNumberOfProcessors;
#else
#ifdef __GNUC__
#warning No known way to discover number of available processors on this system
#warning hwloc_fallback_nbprocessors will default to 1
#endif
  n = -1;
#endif
  if (n >= 1)
    topology->support.discovery->pu = 1;
  else
    n = 1;
  return n;
}
