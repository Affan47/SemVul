FileTimeGet(const char* fname, cmSystemToolsFileTime* t)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  cmSystemToolsWindowsHandle h =
    CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
  if(!h)
    {
    return false;
    }
  if(!GetFileTime(h, &t->timeCreation, &t->timeLastAccess, &t->timeLastWrite))
    {
    return false;
    }
#else
  struct stat st;
  if(stat(fname, &st) < 0)
    {
    return false;
    }
  t->timeBuf.actime = st.st_atime;
  t->timeBuf.modtime = st.st_mtime;
#endif
  return true;
}
