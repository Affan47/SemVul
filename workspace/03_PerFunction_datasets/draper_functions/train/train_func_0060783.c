cleanup_session (char *tty, int pty_fd)
{
  char *line;

# ifdef PATH_TTY_PFX
  if (strncmp (tty, PATH_TTY_PFX, sizeof PATH_TTY_PFX - 1) == 0)
    line = tty + sizeof PATH_TTY_PFX - 1;
  else
# endif
    line = tty;

  if (logout (line))
    logwtmp (line, "", "");

  chmod (tty, 0666);
  chown (tty, 0, 0);
  fchmod (pty_fd, 0666);
  fchown (pty_fd, 0, 0);
}
