sanei_config_open (const char *filename)
{
  char *next, *dir, result[PATH_MAX];
  const char *cfg_dir_list;
  FILE *fp;
  char *copy;

  cfg_dir_list = sanei_config_get_paths ();
  if (!cfg_dir_list)
    {
      DBG(2, "sanei_config_open: could not find config file `%s'\n", filename);
      return NULL;
    }

  copy = strdup (cfg_dir_list);

  for (next = copy; (dir = strsep (&next, DIR_SEP)) != 0; )
    {
      snprintf (result, sizeof (result), "%s%c%s", dir, PATH_SEP, filename);
      DBG(4, "sanei_config_open: attempting to open `%s'\n", result);
      fp = fopen (result, "r");
      if (fp)
	{
	  DBG(3, "sanei_config_open: using file `%s'\n", result);
	  break;
	}
    }
  free (copy);

  if (!fp)
    DBG(2, "sanei_config_open: could not find config file `%s'\n", filename);

  return fp;
}
