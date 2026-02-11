text_load()
{
  struct winsize winsz;
  struct termios new_termios;

  lastloglevel = SUSPEND_ERROR;

  setvbuf(stdout, NULL, _IONBF, 0);


  ioctl(STDOUT_FILENO, TCGETS, (long)&termios);
  new_termios = termios;
  new_termios.c_lflag &= ~ICANON;
  ioctl(STDOUT_FILENO, TCSETSF, (long)&new_termios);


  video_num_lines = 24;
  video_num_columns = 80;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsz) != -1 &&
      winsz.ws_row > 0 && winsz.ws_col > 0) {
    video_num_lines = winsz.ws_row;
    video_num_columns = winsz.ws_col;
    printk("Console is %dx%d.\n", video_num_lines, video_num_columns);
  }


  barwidth = (video_num_columns - 2 * (video_num_columns / 4) - 2);


  vcsa_fd = open("/dev/vcsa0", O_RDONLY);


  return 0;
}
