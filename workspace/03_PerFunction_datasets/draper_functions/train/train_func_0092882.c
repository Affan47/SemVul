get_dirname(char *path)
{
  char *p;


  p = path + strlen(path) - 1;
  while (*p != '/'
#if defined(_WIN32) && !defined(__CYGWIN32__)
	 && *p != '\\'
#endif
	 && p != path) p--;
  if (p == path && *p != '/') *p = '\0';
  else *(p+1) = '\0';
}
