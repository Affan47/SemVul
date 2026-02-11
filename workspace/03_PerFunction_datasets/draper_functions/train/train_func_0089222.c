GetHostMemoryUsed()
{
#if defined(_WIN32)
# if defined(_MSC_VER) && _MSC_VER < 1300
  MEMORYSTATUS stat;
  stat.dwLength = sizeof(stat);
  GlobalMemoryStatus(&stat);
  return (stat.dwTotalPhys - stat.dwAvailPhys)/1024;
# else
  MEMORYSTATUSEX statex;
  statex.dwLength=sizeof(statex);
  GlobalMemoryStatusEx(&statex);
  return (statex.ullTotalPhys - statex.ullAvailPhys)/1024;
# endif
#elif defined(__linux)
  const char *names[3]={"MemTotal:","MemFree:",NULL};
  SystemInformation::LongLong values[2]={SystemInformation::LongLong(0)};
  int ierr=GetFieldsFromFile("/proc/meminfo",names,values);
  if (ierr)
    {
    return ierr;
    }
  SystemInformation::LongLong &memTotal=values[0];
  SystemInformation::LongLong &memFree=values[1];
  return memTotal - memFree;
#elif defined(__APPLE__)
  SystemInformation::LongLong psz=getpagesize();
  if (psz<1)
    {
    return -1;
    }
  const char *names[4]={"Pages active:","Pages inactive:","Pages wired down:",NULL};
  SystemInformation::LongLong values[3]={SystemInformation::LongLong(0)};
  int ierr=GetFieldsFromCommand("vm_stat", names, values);
  if (ierr)
    {
    return -1;
    }
  SystemInformation::LongLong &vmActive=values[0];
  SystemInformation::LongLong &vmInactive=values[1];
  SystemInformation::LongLong &vmWired=values[2];
  return ((vmActive+vmInactive+vmWired)*psz)/1024;
#else
  return 0;
#endif
}
