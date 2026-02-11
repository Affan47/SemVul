readCommand( int fd, char* cmdBuf, size_t len )
{
  unsigned int i;
  char c;
  for ( i = 0; i < len; ++i )
  {
    int result = read( fd, &c, 1 );
    if (result < 0)
      return -1;

    if (result == 0) {
      if (i == 0)
        return -1;

      break;
    }

    if (c == '\n')
      break;

    cmdBuf[ i ] = c;
  }
  cmdBuf[i] = '\0';

  return i;
}
