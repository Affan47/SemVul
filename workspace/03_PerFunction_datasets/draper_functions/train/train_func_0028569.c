gftp_exec (gftp_request * request, int *fdm, int *ptymfd, char **args)
{
  char pts_name[64];
  pid_t child;
  int ptysfd;
  int s[2];

  *pts_name = '\0';
  if ((*ptymfd = _gftp_ptym_open (pts_name, sizeof (pts_name), &ptysfd)) < 0)
    {
      request->logging_function (gftp_logging_error, request->user_data,
                                _("Cannot open master pty %s: %s\n"), pts_name,
                                g_strerror (errno));
      return (-1);
    }

  if (socketpair (AF_LOCAL, SOCK_STREAM, 0, s) < 0)
    {
      request->logging_function (gftp_logging_error, request,
                                 _("Cannot create a socket pair: %s\n"),
                                 g_strerror (errno));
      return (-1);
    }

  if ((child = fork ()) == 0)
    {
      setsid ();

      if ((ptysfd = _gftp_ptys_open (*ptymfd, ptysfd, pts_name)) < 0)
        {
          printf ("Cannot open slave pts %s: %s\n", pts_name,
                  g_strerror (errno));
          return (-1);
        }

      close (s[0]);
      close (*ptymfd);

      _gftp_tty_raw (s[1]);
      _gftp_tty_raw (ptysfd);

      dup2 (s[1], 0);
      dup2 (s[1], 1);
      dup2 (ptysfd, 2);
      _gftp_close_all_fds (ptysfd);

      execvp (args[0], args);

      printf (_("Error: Cannot execute ssh: %s\n"), g_strerror (errno));
      _exit (1);
    }
  else if (child > 0)
    {
      close (s[1]);

      *fdm = s[0];
      _gftp_tty_raw (s[0]);
      _gftp_tty_raw (*ptymfd);

      return (child);
    }
  else
    {
      request->logging_function (gftp_logging_error, request->user_data,
                                 _("Cannot fork another process: %s\n"),
                                 g_strerror (errno));
      return (-1);
    }
}
