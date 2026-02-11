generic_cache_create_dir(char * dirname)
{
  struct stat buf;
  int r;

  r = stat(dirname, &buf);
  if (r != 0) {

#ifdef WIN32
	r = mkdir(dirname);
#else
    r = mkdir(dirname, 0700);
#endif

    if (r < 0)
      return MAIL_ERROR_FILE;
  }
  else {
    if (!S_ISDIR(buf.st_mode))
      return MAIL_ERROR_FILE;
  }

  return MAIL_NO_ERROR;
}
