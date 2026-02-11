event_cb (ev::timer &w, int)
{
  if (events)
    {
      if (events & EVENT_SHUTDOWN)
        {
          slog (L_INFO, _("preparing shutdown..."));

          shutdown_all ();
          remove_pid (conf.pidfilename);
          slog (L_INFO, _("exiting."));
          exit (EXIT_SUCCESS);
        }

      if (events & EVENT_RECONNECT)
        {
          slog (L_INFO, _("forced reconnect."));

          reconnect_all ();
        }

      events = 0;
    }
}
