afNewAso (list, key, mode, generation)
     Af_revlist *list;
     Af_key     *key;
     int        mode;
     int        generation;
{
  int freepos, insertpos, i;

  if (mode != AF_CLASS_SOURCE)
    FAIL ("newAso", "invalid mode", AF_EINTERNAL, ERROR);

  key->af_ldes = list;


  if (afRefreshList (list, AF_DATA) == ERROR)
    return (ERROR);

  if ((freepos = af_gfreepos (list)) == ERROR)
    FAIL ("newAso", "too many new revisions", AF_EINTERNAL, ERROR);

  if (generation == AF_LASTVERS)
    key->af_lpos = freepos;
  else {

    if ((insertpos = af_glastgenpos (list, generation)) == ERROR)
      insertpos = freepos;
    insertpos++;
    for (i=freepos; i>insertpos; i--)
      if (list->af_list[i-1].af_nrefs > 0)
	FAIL ("newAso", "cannot create hole in history (reference count not zero)", AF_EMISC, ERROR);
    for (i=freepos; i>insertpos; i--)
      list->af_list[i] = list->af_list[i-1];
    key->af_lpos = insertpos;
  }

  VATTR(key).af_nrefs = 0;
  afIncreaseAccess (key);

  return (AF_OK);
}
