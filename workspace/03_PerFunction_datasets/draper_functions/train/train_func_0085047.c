movefile(char *oldpath, char *newpath)
{
  int ret;

#ifdef HAVE_RENAME

  if (!rename(oldpath, newpath))
    return 0;
#endif


  ret = copyfile(oldpath, newpath);
  if (!ret)
    unlink(oldpath);
  return ret;
}
