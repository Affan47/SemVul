SetUnzipBaseDir(const TCHAR *dir)
{
#ifdef ZIP_STD
 strncpy(rootdir,dir,MAX_PATH-1);
#else
  _tcsncpy_s(rootdir,MAX_PATH,dir,MAX_PATH-1);
#endif
  TCHAR *lastchar = &rootdir[_tcslen(rootdir)-1];
  if (*lastchar!='\\' && *lastchar!='/') {lastchar[1]='/'; lastchar[2]=0;}
  return ZR_OK;
}
