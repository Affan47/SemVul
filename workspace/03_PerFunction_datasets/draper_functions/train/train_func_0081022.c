tcl_erasenotes STDVAR
{
  FILE *f, *g;
  char s[601], *to, *s1;
  int read, erased;
  int nl[128];

  BADARGS(3, 3, " handle noteslist#");

  if (!get_user_by_handle(userlist, argv[1])) {
    Tcl_AppendResult(irp, "-1", NULL);
    return TCL_OK;
  }
  if (!notefile[0]) {
    Tcl_AppendResult(irp, "-2", NULL);
    return TCL_OK;
  }
  f = fopen(notefile, "r");
  if (f == NULL) {
    Tcl_AppendResult(irp, "-2", NULL);
    return TCL_OK;
  }
  sprintf(s, "%s~new", notefile);
  g = fopen(s, "w");
  if (g == NULL) {
    fclose(f);
    Tcl_AppendResult(irp, "-2", NULL);
    return TCL_OK;
  }
  chmod(s, userfile_perm);
  read = 0;
  erased = 0;
  notes_parse(nl, (argv[2][0] == 0) ? "-" : argv[2]);
  while (!feof(f) && fgets(s, 600, f)) {
    if (s[strlen(s) - 1] == '\n')
      s[strlen(s) - 1] = 0;
    if (!feof(f)) {
      rmspace(s);
      if ((s[0]) && (s[0] != '#') && (s[0] != ';')) {
        s1 = s;
        to = newsplit(&s1);
        if (!egg_strcasecmp(to, argv[1])) {
          read++;
          if (!notes_in(nl, read))
            fprintf(g, "%s %s\n", to, s1);
          else
            erased++;
        } else
          fprintf(g, "%s %s\n", to, s1);
      }
    }
  }
  sprintf(s, "%d", erased);
  Tcl_AppendResult(irp, s, NULL);
  fclose(f);
  fclose(g);
  unlink(notefile);
  sprintf(s, "%s~new", notefile);
  movefile(s, notefile);
  return TCL_OK;
}
