update_termsize(int sig) {
#ifdef TIOCGWINSZ
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 &&
      ws.ws_row > 0 && ws.ws_col > 0) {
    termsize.cols = ws.ws_col;
    termsize.lines = ws.ws_row;
  } else {
    termsize.lines = 25;
    termsize.cols = 80;
  }
#ifdef SIGWINCH
  if (sig == SIGWINCH)
    _sigwinch = 1;
  RESIGNAL(SIGWINCH, &update_termsize);
#endif
#endif
}
