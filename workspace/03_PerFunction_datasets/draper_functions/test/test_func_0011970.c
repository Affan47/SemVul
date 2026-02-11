_bmc_watchdog_args_validate (struct bmc_watchdog_arguments *cmd_args)
{
  int count;

  if (cmd_args->help)
    _usage (cmd_args);

  if (cmd_args->version)
    {
      fprintf (stderr, "%s\n", argp_program_version);
      exit (1);
    }

  count = cmd_args->set + cmd_args->get + cmd_args->reset +
    cmd_args->start + cmd_args->stop + cmd_args->clear + cmd_args->daemon;
  if (!count)
    _usage (cmd_args);
  if (count > 1)
    {
      fprintf (stderr, "Only one command can be specified\n");
      exit (1);
    }

  if (((cmd_args->get
        || cmd_args->reset
        || cmd_args->start
        || cmd_args->stop
        || cmd_args->clear)
       && (cmd_args->timer_use
           || cmd_args->stop_timer
           || cmd_args->log
           || cmd_args->timeout_action
           || cmd_args->pre_timeout_interrupt
           || cmd_args->pre_timeout_interval
           || cmd_args->clear_bios_frb2
           || cmd_args->clear_bios_post
           || cmd_args->clear_sms_os
           || cmd_args->clear_oem
           || cmd_args->initial_countdown_seconds
           || cmd_args->start_after_set
           || cmd_args->reset_after_set
           || cmd_args->reset_if_running
           || cmd_args->reset_period))
      || (cmd_args->set
          && cmd_args->reset_period)
      || (cmd_args->daemon
          && (cmd_args->stop_timer
              || cmd_args->start_after_set
              || cmd_args->reset_after_set
              || cmd_args->reset_if_running))
      || ((cmd_args->set
           || cmd_args->get
           || cmd_args->reset
           || cmd_args->stop
           || cmd_args->clear)
          && (cmd_args->gratuitous_arp
              || cmd_args->arp_response)))
    {
      char *cmdstr;

      cmdstr = _cmd_string (cmd_args);
      fprintf (stderr, "Invalid command option specified for '%s' command\n", cmdstr);
      exit (1);
    }
}
