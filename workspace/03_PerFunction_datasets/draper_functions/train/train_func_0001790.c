GNUNET_log_setup (const char *comp, const char *loglevel, const char *logfile)
{
  FILE *altlog;
  int dirwarn;
  char *fn;
  const char *env_logfile = NULL;
  int altlog_fd;

  min_level = get_type (loglevel);
#if !defined(GNUNET_CULL_LOGGING)
  parse_all_definitions ();
#endif
#ifdef WINDOWS
  QueryPerformanceFrequency (&performance_frequency);
#endif
  GNUNET_free_non_null (component);
  GNUNET_asprintf (&component, "%s-%d", comp, getpid ());
  GNUNET_free_non_null (component_nopid);
  component_nopid = GNUNET_strdup (comp);

  env_logfile = getenv ("GNUNET_FORCE_LOGFILE");
  if ((env_logfile != NULL) && (strlen (env_logfile) > 0))
    logfile = env_logfile;

  if (logfile == NULL)
    return GNUNET_OK;
  fn = GNUNET_STRINGS_filename_expand (logfile);
  if (NULL == fn)
    return GNUNET_SYSERR;
  dirwarn = (GNUNET_OK != GNUNET_DISK_directory_create_for_file (fn));
#if WINDOWS
  altlog_fd = OPEN (fn, O_APPEND |
                        O_BINARY |
                        O_WRONLY | O_CREAT,
                        _S_IREAD | _S_IWRITE);
#else
  altlog_fd = OPEN (fn, O_APPEND |
                        O_WRONLY | O_CREAT,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
#endif
  if (altlog_fd != -1)
  {
    int dup_return;
    if (GNUNET_stderr != NULL)
      fclose (GNUNET_stderr);
    dup_return = dup2 (altlog_fd, 2);
    (void) close (altlog_fd);
    if (dup_return != -1)
    {
      altlog = fdopen (2, "ab");
      if (altlog == NULL)
      {
        (void) close (2);
        altlog_fd = -1;
      }
    }
    else
    {
      altlog_fd = -1;
    }
  }
  if (altlog_fd == -1)
  {
    GNUNET_log_strerror_file (GNUNET_ERROR_TYPE_ERROR, "open", fn);
    if (dirwarn)
      GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                  _("Failed to create or access directory for log file `%s'\n"),
                  fn);
    GNUNET_free (fn);
    return GNUNET_SYSERR;
  }
  GNUNET_free (fn);
  GNUNET_stderr = altlog;
  return GNUNET_OK;
}
