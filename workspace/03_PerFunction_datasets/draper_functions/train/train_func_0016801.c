_init_bmc_watchdog (int facility, int err_to_stderr)
{
  assert (facility == LOG_CRON || facility == LOG_DAEMON);

  openlog (err_progname, LOG_ODELAY | LOG_PID, facility);

  if (!cmd_args.no_logging)
    {
      if ((logfile_fd = open ((cmd_args.logfile) ? cmd_args.logfile : BMC_WATCHDOG_LOGFILE_DEFAULT,
                              O_WRONLY | O_CREAT | O_APPEND,
                              S_IRUSR | S_IWUSR)) < 0)
        {
          if (err_to_stderr)
            _err_exit ("Error opening logfile '%s': %s",
                       (cmd_args.logfile) ? cmd_args.logfile : BMC_WATCHDOG_LOGFILE_DEFAULT,
                       strerror (errno));
          else
            _syslog (LOG_ERR, "Error opening logfile '%s': %s",
                     (cmd_args.logfile) ? cmd_args.logfile : BMC_WATCHDOG_LOGFILE_DEFAULT,

                     strerror (errno));
          exit (1);
        }
    }

  if (_init_ipmi () < 0)
    {
      if (err_to_stderr)
        _err_exit ("_init_ipmi: %s", strerror (errno));
      else
        _syslog (LOG_ERR, "_init_ipmi: %s", strerror (errno));
      exit (1);
    }
}
