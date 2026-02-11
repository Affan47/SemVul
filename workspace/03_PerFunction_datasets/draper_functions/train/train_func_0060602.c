wait_hydra_output(gpointer data) {
  static int stdout_ok = TRUE, stderr_ok = TRUE;
  fd_set rset;
  struct timeval tv;
  int result, max;
  int *fd = data;
  int status;

  g_assert((stdout_ok == TRUE) || (stderr_ok == TRUE));

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rset);
  max = -1;

  if (stdout_ok) {
    FD_SET(fd[0], &rset);
    max = fd[0];
  }
  if (stderr_ok) {
    FD_SET(fd[1], &rset);
    if (-1 == max)
      max = fd[1];
    else
      max = fd[0] > fd[1] ? fd[0] : fd[1];
  }

  result = select(max + 1, &rset, NULL, NULL, &tv);

  if (result < 0)
    g_error("wait_hydra_output: select returned negative!");
  else if (result == 0)
    return TRUE;

  if (stdout_ok && FD_ISSET(fd[0], &rset))
    stdout_ok = read_into(fd[0]);
  if (stderr_ok && FD_ISSET(fd[1], &rset))
    stderr_ok = read_into(fd[1]);

  if (!(stdout_ok || stderr_ok)) {
    waitpid(hydra_pid, &status, 0);
    hydra_pid = 0;
    stdout_ok = stderr_ok = TRUE;
    return FALSE;
  } else
    return TRUE;
}
