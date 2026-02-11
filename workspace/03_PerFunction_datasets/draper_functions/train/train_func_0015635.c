af_gbusname (pathname, name, type)
     char *pathname;
     char *name, *type;
{
  char busyname[PATH_MAX];

  if (!pathname || !(*pathname))
    strcpy (busyname, name);
  else if (!strcmp (pathname, "/"))
    sprintf (busyname, "/%s", name);
  else
    sprintf (busyname, "%s/%s", pathname, name);
  if (type && type[0]) {
    strcat (busyname, ".");
    strcat (busyname, type);
  }
  return (af_entersym (busyname));
}
