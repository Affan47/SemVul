set_window_size (int rows, int cols, char const *device_name)
{
  struct winsize win;

  if (get_win_size (STDIN_FILENO, &win))
    {
      if (errno != EINVAL)
        error (EXIT_FAILURE, errno, "%s", device_name);
      memset (&win, 0, sizeof (win));
    }

  if (rows >= 0)
    win.ws_row = rows;
  if (cols >= 0)
    win.ws_col = cols;

# ifdef TIOCSSIZE


  if (win.ws_row == 0 || win.ws_col == 0)
    {
      struct ttysize ttysz;

      ttysz.ts_lines = win.ws_row;
      ttysz.ts_cols = win.ws_col;

      win.ws_row = 1;
      win.ws_col = 1;

      if (ioctl (STDIN_FILENO, TIOCSWINSZ, (char *) &win))
        error (EXIT_FAILURE, errno, "%s", device_name);

      if (ioctl (STDIN_FILENO, TIOCSSIZE, (char *) &ttysz))
        error (EXIT_FAILURE, errno, "%s", device_name);
      return;
    }
# endif

  if (ioctl (STDIN_FILENO, TIOCSWINSZ, (char *) &win))
    error (EXIT_FAILURE, errno, "%s", device_name);
}
