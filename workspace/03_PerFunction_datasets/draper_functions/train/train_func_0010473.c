get_error(const char *err_str) {
#ifdef _WIN32
  return GetLastError();
#else


  unsigned long ret = errno;
  if (! ret && err_str && strstr(err_str, "No such file"))
	ret = OS_E_FILENOTFOUND;
  return ret;
#endif
}
