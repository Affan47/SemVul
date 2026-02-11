key_avail (FILE * stream)
{
  int tty = fileno (stream);
  fd_set selin;
  static struct timeval now = { 0 , 0 };

  setvbuf(stream, NULL, _IONBF, 0);
  if(!terminal_prepped && stream == stdin)
    prep_terminal();

  FD_ZERO(&selin);
  FD_SET(tty, &selin);
  return select(1, &selin, NULL, NULL, &now);
}
