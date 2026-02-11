afGetAso (syspath, name, type, gen, rev, key)
     char   *syspath, *name, *type;
     int    gen, rev;
     Af_key *key;

{
  register Af_revlist *list;
  register char       *pathsym, *namesym, *typesym;
  Af_key              *keyptr;


  pathsym = af_entersym (syspath);
  namesym = af_entersym (name);
  typesym = af_entersym (type);

  if ((list = afInitList (pathsym, namesym, typesym)) == NULL)
    FAIL ("getkey", "", AF_ENOREV, ERROR);

  key->af_ldes = list;


  if ((gen < 0) || (rev < 0)) {
    switch (rev) {
    case AF_BUSYVERS:
      if (af_buildkey (list, gen, rev, key) == ERROR)
	FAIL ("getkey", "", AF_ENOREV, ERROR);
      break;
    case AF_LASTVERS:
      if (gen == AF_LASTVERS) {
	if ((keyptr = af_glastkey (list)) == NULL)
	  FAIL ("getkey", "", AF_ENOREV, ERROR);
	key->af_lpos = keyptr->af_lpos;
      }
      else {
	if ((keyptr = af_glastgenkey (list, gen)) == NULL)
	  FAIL ("getkey", "", AF_ENOREV, ERROR);
	key->af_lpos = keyptr->af_lpos;
      }
      break;
    case AF_FIRSTVERS:
      if (list->af_nrevs == 0)
	FAIL ("getkey", "", AF_ENOREV, ERROR);
      if (gen == AF_FIRSTVERS) {
	key->af_lpos = 0;
	while ((VATTR(key).af_state == AF_BUSY) || (!(VATTR(key).af_class & AF_VALID))) {
	  if (key->af_lpos++ == list->af_listlen-1)
	    FAIL ("getkey", "", AF_ENOREV, ERROR);
	}
      }
      else {
	key->af_lpos = 1;
	while ((!(VATTR(key).af_class & AF_VALID)) || (VATTR(key).af_gen != gen)) {
	  if (key->af_lpos++ == list->af_listlen-1)
	    FAIL ("getkey", "", AF_ENOREV, ERROR);
	}
      }
      break;
    default: FAIL ("getkey", "", AF_ENOREV, ERROR);
    }
  }
  else {
    if (af_buildkey (list, gen, rev, key) == ERROR)
      FAIL ("getkey", "", AF_ENOREV, ERROR);
  }

  afIncreaseAccess (key);
  return (AF_OK);
}
