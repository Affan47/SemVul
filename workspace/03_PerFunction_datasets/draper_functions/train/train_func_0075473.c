afReadName (archname)
     char *archname;
{
  register FILE *archfile;
  register char *itemptr;
  char          newarname[PATH_MAX+1], line[AF_LINESIZ];
  static char   name[NAME_MAX+1];

  archname[strlen (archname)-1] = AF_OLD_ARCHEXT;
  if ((archfile = fopen (archname, "r")) == NULL) {
    strcpy (newarname, afArchivePath (af_uniqpath (".")));
    strcat (newarname, "/");
    strcat (newarname, archname);
    if ((archfile = fopen (newarname, "r")) == NULL) {
      strcpy (name, archname + strlen (AF_OLD_ATFSFILEID));
      name[strlen(name)-1] = '\0';
      return (name);
    }
  }

  fgets (line, AF_LINESIZ, archfile);
  fgets (line, AF_LINESIZ, archfile);

  itemptr = xfirstitem (line);
  itemptr = xnextitem (itemptr);
  itemptr = xnextitem (itemptr);
  itemptr = xnextitem (itemptr);
  strcpy (name, itemptr);
  itemptr = xnextitem (itemptr);
  if (strcmp (itemptr, AF_NOSTRING)) {
    strcat (name, ".");
    strcat (name, itemptr);
  }

  fclose (archfile);
  return (name);
}
