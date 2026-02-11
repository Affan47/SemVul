__hscore_readdir( HsAddr dirPtr, HsAddr pDirEnt )
{
  struct dirent **pDirE = (struct dirent**)pDirEnt;
#if HAVE_READDIR_R
  struct dirent* p;
  int res;
  static unsigned int nm_max = (unsigned int)-1;

  if (pDirE == NULL) {
    return -1;
  }
  if (nm_max == (unsigned int)-1) {
#ifdef NAME_MAX
    nm_max = NAME_MAX + 1;
#else
    nm_max = pathconf(".", _PC_NAME_MAX);
    if (nm_max == -1) { nm_max = 255; }
    nm_max++;
#endif
  }
  p = (struct dirent*)malloc(sizeof(struct dirent) + nm_max);
  if (p == NULL) return -1;
  res = readdir_r((DIR*)dirPtr, p, pDirE);
  if (res != 0) {
      *pDirE = NULL;
      free(p);
  }
  else if (*pDirE == NULL) {

    free(p);
  }
  return res;
#else

  if (pDirE == NULL) {
    return -1;
  }

  *pDirE = readdir((DIR*)dirPtr);
  if (*pDirE == NULL) {
    return -1;
  } else {
    return 0;
  }
#endif
}
