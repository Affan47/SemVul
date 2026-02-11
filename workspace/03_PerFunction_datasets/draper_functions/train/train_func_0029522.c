checkfile(const char *filename)
{
  struct stat filestat;
  if(stat(filename,&filestat)==0) return 1;
  else if(errno == error_noent) return 0;
  return -1;
}
