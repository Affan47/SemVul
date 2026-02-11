display_logfiles(char *logdir, char *default_logfile)
{
    int  x;
    char *seps = "/";
    char *token;
    char *curlog = NULL;
    char **logfiles;
    int at_least_one=0;

    if (default_logfile != NULL) {
      token = strtok(default_logfile, seps);
      while(token != NULL) {
        curlog = token;
        token = strtok(NULL, seps);
      }
    }
    fprintf(stdout, "%s", getResourceString(DBT_DISPLAY_LOGFILE_SELECT_BEGIN));

    logfiles = list_directory(logdir, 0);

    for(x=0; logfiles && logfiles[x]; x++) {
      if (curlog && !strcmp(curlog, logfiles[x])) {
        fprintf(stdout, getResourceString(DBT_DISPLAY_LOGFILE_VALUE_SELECTED),
                logfiles[x], logfiles[x]);
      }
      else {
        fprintf(stdout, getResourceString(DBT_DISPLAY_LOGFILE_SELECT_VALUE),
                logfiles[x], logfiles[x]);
      }
      at_least_one = 1;
    }

    if(!at_least_one)
      fprintf(stdout, "%s", getResourceString(DBT_DISPLAY_LOGFILE_NO_LOG));

    fprintf(stdout, "%s", getResourceString(DBT_DISPLAY_LOGFILE_SELECT_END));

}
