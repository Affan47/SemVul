af_getkey (syspath, name, type, gen, rev, key)
     char   *syspath, *name, *type;
     int    gen, rev;
     Af_key *key;
{
  char *uniqPath = af_uniqpath (af_entersym (syspath));


  if (!name || !(*name)) {
    if (type && *type)
      FAIL ("getkey", "cannot handle empty name and non-empty type", AF_EMISC, ERROR);
    name = ".";
  }


  if (!strcmp (name, "..") && (!type || !(*type)))
    FAIL ("getkey", "cannot handle name '..'", AF_EMISC, ERROR);


  if (!strcmp (name, ".") && (!type || !(*type)) && strcmp (uniqPath, "/"))
    return (afGetAso (af_afpath (uniqPath), af_afname (uniqPath), af_aftype (uniqPath), gen, rev, key));
  else
    return (afGetAso (uniqPath, name, type, gen, rev, key));
}
