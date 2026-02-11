get_mtime (char const *filename, struct timespec *mtime)
{
  struct stat finfo;
  bool ok = (stat (filename, &finfo) == 0);
#ifdef lint
  static struct timespec const zero;
  *mtime = zero;
#endif
  if (ok)
    *mtime = get_stat_mtime (&finfo);
  return ok;
}
