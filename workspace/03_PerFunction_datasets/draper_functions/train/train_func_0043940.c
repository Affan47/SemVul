idle_do_pending_events (gpointer data)
{
  EggSMClientXSMP *xsmp = data;
  EggSMClient *client = data;

  gdk_threads_enter ();

  xsmp->idle = 0;

  if (xsmp->waiting_to_emit_quit)
    {
      xsmp->waiting_to_emit_quit = FALSE;
      egg_sm_client_quit (client);
      goto out;
    }

  if (xsmp->waiting_to_emit_quit_cancelled)
    {
      xsmp->waiting_to_emit_quit_cancelled = FALSE;
      egg_sm_client_quit_cancelled (client);
      xsmp->state = XSMP_STATE_IDLE;
    }

  if (xsmp->waiting_to_save_myself)
    {
      xsmp->waiting_to_save_myself = FALSE;
      do_save_yourself (xsmp);
    }

 out:
  gdk_threads_leave ();
  return FALSE;
}
