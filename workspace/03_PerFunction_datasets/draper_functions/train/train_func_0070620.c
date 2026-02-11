start_server (const char *pgmname)
{
  int rp[2];
  int wp[2];
  pid_t pid;

  if (pipe (rp) < 0)
    die_1 ("pipe creation failed: %s", strerror (errno));
  if (pipe (wp) < 0)
    die_1 ("pipe creation failed: %s", strerror (errno));

  fflush (stdout);
  fflush (stderr);
  pid = fork ();
  if (pid < 0)
    die_0 ("fork failed");

  if (!pid)
    {
      const char *arg0;

      arg0 = strrchr (pgmname, '/');
      if (arg0)
        arg0++;
      else
        arg0 = pgmname;

      if (wp[0] != STDIN_FILENO)
        {
          if (dup2 (wp[0], STDIN_FILENO) == -1)
            die_1 ("dup2 failed in child: %s", strerror (errno));
          close (wp[0]);
        }
      if (rp[1] != STDOUT_FILENO)
        {
          if (dup2 (rp[1], STDOUT_FILENO) == -1)
            die_1 ("dup2 failed in child: %s", strerror (errno));
          close (rp[1]);
        }
      if (!opt_verbose)
        {
	  int fd = open ("/dev/null", O_WRONLY);
	  if (fd == -1)
	    die_1 ("can't open `/dev/null': %s", strerror (errno));
          if (dup2 (fd, STDERR_FILENO) == -1)
            die_1 ("dup2 failed in child: %s", strerror (errno));
	  close (fd);
        }

      close (wp[1]);
      close (rp[0]);
      execl (pgmname, arg0, "--server", NULL);
      die_2 ("exec failed for `%s': %s", pgmname, strerror (errno));
    }
  close (wp[0]);
  close (rp[1]);
  server_send_fd = wp[1];
  server_recv_fd = rp[0];

  read_assuan (server_recv_fd);
  if (recv_type != LINE_OK)
    die_0 ("no greating message");
}
