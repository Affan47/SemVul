est_gettimeofday(void){
#if defined(_SYS_MSVC_) || defined(_SYS_MINGW_)
  SYSTEMTIME st;
  struct tm ts;
  GetLocalTime(&st);
  memset(&ts, 0, sizeof(ts));
  ts.tm_year = st.wYear - 1900;
  ts.tm_mon = st.wMonth - 1;
  ts.tm_mday = st.wDay;
  ts.tm_hour = st.wHour;
  ts.tm_min = st.wMinute;
  ts.tm_sec = st.wSecond;
  return (double)mktime(&ts) * 1000 + (double)st.wMilliseconds;
#else
  struct timeval tv;
  struct timezone tz;
  if(gettimeofday(&tv, &tz) == -1) return 0.0;
  return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
#endif
}
