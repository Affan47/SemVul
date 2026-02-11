quit (int signum)
{
  static int running = 0;
  int i;

  if (signum)
    DBG (DBG_ERR, "quit: received signal %d\n", signum);

  if (running)
    {
      DBG (DBG_ERR, "quit: already active, returning\n");
      return;
    }
  running = 1;

  for (i = 0; i < num_handles; ++i)
    if (handle[i].inuse)
      sane_close (handle[i].handle);

  sane_exit ();
  sanei_w_exit (&wire);
  if (handle)
    free (handle);
  DBG (DBG_WARN, "quit: exiting\n");
  if (log_to_syslog)
    closelog ();
  exit (EXIT_SUCCESS);
}
