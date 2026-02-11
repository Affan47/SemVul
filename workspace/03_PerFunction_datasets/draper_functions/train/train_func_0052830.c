read_sound_config_file (char *filename)
{
  FILE *fs;
  char *buf = 0;
  size_t bufsize = 0;
  int firstline = 0, endline = 0;
  char *expfilename = rsc_expand (filename);
  char *dir = dir_name (expfilename);
  size_t dirlen = strlen (dir);

  dmsg (D_SECTION | D_FILE, "reading sound config file: %s ...", expfilename);

  fs = fopen (expfilename, "r");

  if (!fs) {
    dmsg (D_SECTION | D_FILE, "... could not open.");
    dperror ("fopen");
    free (expfilename);
    free (dir);
    return 0;
  }

  while (getshline_numbered (&firstline, &endline, &buf, &bufsize, fs) != -1) {
    char *alias = strtok (buf, ":\n");
    char *file = strtok (0, ":\n");
    char *title = strtok (0, ":\n");
    char *author = strtok (0, "\n");
    if (!alias || !alias[0])
      wmsg (_("%s:%d: missing alias name"), filename, firstline);
    else if (!file || !file[0])
      wmsg (_("%s:%d: missing file name"), filename, firstline);
    else if (!title || !title[0])
      wmsg (_("%s:%d: missing title"), filename, firstline);
    else if (!author || !author[0])
      wmsg (_("%s:%d: missing author"), filename, firstline);
    else {
      if (dir && file[0] != '/') {
	char *tmp = malloc (dirlen + 1 + strlen (file) + 1);
	sprintf (tmp, "%s/%s", dir, file);
	add_sound_track_cons (alias, tmp, title, author);
	free (tmp);
      } else {
	add_sound_track_cons (alias, file, title, author);
      }
    }
  }
  fclose (fs);
  free (buf);
  free (dir);
  free (expfilename);
  dmsg (D_SECTION|D_FILE,"... done.");

  return 0;
}
