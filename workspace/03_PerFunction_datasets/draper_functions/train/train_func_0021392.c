terminal_screen_get_current_dir (TerminalScreen *screen)
{
  TerminalScreenPrivate *priv = screen->priv;
  char *cwd;

  if (priv->pty_fd != -1) {
#if 0

    cwd = cwd_of_pid (tcgetpgrp (priv->pty_fd));
    if (cwd != NULL)
      return cwd;
#endif


    cwd = cwd_of_pid (priv->child_pid);
    if (cwd != NULL)
      return cwd;
  }

  return NULL;
}
