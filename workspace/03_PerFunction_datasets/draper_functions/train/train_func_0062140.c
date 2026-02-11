af_cachenames (path, pattern)
     char *path, *pattern;
{
  char       *pathSym, **nameList, *reMsg, *nameSym;
  int        nameListSize, nameCount=0, i, j, maxindex;
  Af_revlist *objCacheList;


  if ((nameList = (char **)malloc ((unsigned) (AF_SEGLEN * sizeof (char *)))) == NULL)
    FAIL ("cachenames", "malloc", AF_ESYSERR, NULL);
  nameListSize = AF_SEGLEN;
  nameList[0] = NULL;


  pathSym = af_uniqpath (af_entersym (path));

  if ((objCacheList = afInitObjCache (pathSym)) == NULL)
    if (af_errno == AF_ENOATFSDIR)
      return (nameList);
    else
      return (NULL);


  if ((reMsg = re_comp (pattern)))
    af_wng ("cachenames", reMsg);


  maxindex = objCacheList->af_nrevs-1;
  for (i=0; i <= maxindex; i++) {

    if (!(objCacheList->af_list[i].af_class & AF_VALID)) {
      if (++maxindex == objCacheList->af_listlen)
	FATAL ("cachenames", "bad revision count", AF_EINCONSIST, NULL);
      continue;
    }


    nameSym = af_gbusname (NULL, objCacheList->af_list[i].af_name, objCacheList->af_list[i].af_type);
    for (j=0; j<nameCount; j++) {
      if (nameSym == nameList[j])
	break;
    }
    if (!re_exec (nameSym))
      continue;
    if (j == nameCount)
      nameList[nameCount++] = nameSym;
    if (nameCount == nameListSize) {
      if ((nameList = (char **)realloc (nameList, (unsigned) ((nameListSize+AF_SEGLEN) * sizeof (char *)))) == NULL)
	FAIL ("cachenames", "realloc", AF_ESYSERR, NULL);
      nameListSize += AF_SEGLEN;
    }
  }
  nameList[nameCount] = NULL;
  return (nameList);
}
