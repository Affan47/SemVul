qh_init_qhull_command(int argc, char *argv[]) {
  int i;

  strcpy (qh qhull_command, argv[0]);
  for (i=1; i<argc; i++) {
    if (strlen (qh qhull_command) + strlen(argv[i]) + 1 < sizeof(qh qhull_command)) {
      strcat (qh qhull_command, " ");
      strcat (qh qhull_command, argv[i]);
    }else qhull_fatal(67);

  }
}
