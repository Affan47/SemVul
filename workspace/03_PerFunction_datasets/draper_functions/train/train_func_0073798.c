configcachefile(void *opt, char *cmd, char *arg1, char *arg2, int rc) {

  Logfile **logfile = (Logfile **)opt;
  extern logical iscache;


  if (rc > 1) {
    longwarn(cmd, arg1, arg2, rc);
    rc = 1;
  }
  if (strcaseeq(arg1, "NONE")) {
    logfile[1] = NULL;
    return;
  }
  iscache = TRUE;
  configlogfile(opt, cmd, arg1, NULL, rc);
  iscache = FALSE;
}
