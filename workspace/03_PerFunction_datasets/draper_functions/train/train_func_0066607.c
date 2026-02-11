buffindexed_getartinfo(const char *group, ARTNUM artnum, TOKEN *token)
{
  GROUPLOC	gloc;
  void		*handle;
  bool		retval, grouplocked = false;

  if (Gib != NULL) {
    if (Cachesearch != NULL && strcmp(Cachesearch->group, group) != 0) {
      free(Gib);
      Gib = NULL;
      free(Cachesearch->group);
      free(Cachesearch);
      Cachesearch = NULL;
    } else {
      if (gettoken(artnum, token))
	return true;
      else {

	gloc = GROUPfind(group, false);
	if (GROUPLOCempty(gloc)) {
	  return false;
	}
	GROUPlock(gloc, INN_LOCK_WRITE);
	if ((Cachesearch != NULL) && (GROUPentries[gloc.recno].count == Cachesearch->count)) {

	  GROUPlock(gloc, INN_LOCK_UNLOCK);
	  return false;
	} else {
	  grouplocked = true;
	  free(Gib);
	  Gib = NULL;
	  if (Cachesearch != NULL) {
	    free(Cachesearch->group);
	    free(Cachesearch);
	    Cachesearch = NULL;
	  }
	}
      }
    }
  }
  if (!grouplocked) {
    gloc = GROUPfind(group, false);
    if (GROUPLOCempty(gloc)) {
      return false;
    }
    GROUPlock(gloc, INN_LOCK_WRITE);
  }
  if (!(handle = ovopensearch(group, artnum, artnum, false))) {
    GROUPlock(gloc, INN_LOCK_UNLOCK);
    return false;
  }
  retval = buffindexed_search(handle, NULL, NULL, NULL, token, NULL);
  ovclosesearch(handle, false);
  GROUPlock(gloc, INN_LOCK_UNLOCK);
  return retval;
}
