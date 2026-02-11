watch_fopen(char *filename, time_t *pfile_modify_time)
{
  FILE *fp;
  char fname[256];

  get_gcin_user_or_sys_fname(filename, fname);

  if ((fp=fopen(fname, "rb"))==NULL) {
#if UNIX
    strcat(strcat(strcpy(fname, TableDir), "/"), filename);
#else
    strcat(strcat(strcpy(fname, TableDir), "\\"), filename);
#endif

    if ((fp=fopen(fname, "rb"))==NULL)
     return NULL;
  }

#if UNIX
  struct stat st;
  fstat(fileno(fp), &st);
#else
  struct _stat st;
  _fstat(fileno(fp), &st);
#endif

  if (st.st_mtime == *pfile_modify_time) {
    fclose(fp);
    return NULL;
  }

  *pfile_modify_time = st.st_mtime;
  return fp;
}
