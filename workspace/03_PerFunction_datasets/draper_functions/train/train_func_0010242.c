af_crkey (path, name, type, key)
     char *path;
     char *name, *type;
     Af_key *key;
{
  char *busyname, *uniqpath = af_uniqpath (af_entersym(path));
  FILE *busyfile;
  struct stat bibuf;


  if (!name || !(*name)) {
    name = ".";
    if (type && *type)
      FAIL ("crkey", "cannot handle empty name and non-empty type", AF_EMISC, ERROR);
    name = ".";
  }


  if (!strcmp (name, "..") && (!type || !(*type)))
    FAIL ("crkey", "cannot handle name '..'", AF_EMISC, ERROR);


  if (!strcmp (name, ".") && (!type || !(*type))) {
    busyname = uniqpath;
    uniqpath = af_afpath (busyname);
    name = af_afname (busyname);
    type = af_aftype (busyname);
  }
  else
    busyname = af_gbusname (uniqpath, name, type);


  if ((stat (busyname, &bibuf)) == ERROR) {
    if ((busyfile = fopen (busyname, "w")) == NULL)
      FAIL ("crkey", "fopen", AF_ESYSERR, ERROR);
    fclose (busyfile);
    stat (busyname, &bibuf);
  }


  if (afGetAso (uniqpath, name, type, AF_BUSYVERS, AF_BUSYVERS, key) == ERROR)
    return (ERROR);

  return (AF_OK);
}
