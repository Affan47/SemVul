updateLoadAvg( void )
{
  size_t n;
  int fd;

  if ( LoadAvgOK < 0 )
    return -1;

  if ( ( fd = open( "/proc/loadavg", O_RDONLY ) ) < 0 ) {
    if ( LoadAvgOK != 0 )
      print_error( "Cannot open file \'/proc/loadavg\'!\n"
                   "The kernel needs to be compiled with support\n"
                   "for /proc file system enabled!\n" );
    return -1;
  }

  n = read( fd, LoadAvgBuf, LOADAVGBUFSIZE - 1 );
  if ( n == LOADAVGBUFSIZE - 1 || n <= 0 ) {
    log_error( "Internal buffer too small to read \'/proc/loadavg\'" );

    close( fd );
    return -1;
  }

  close( fd );
  LoadAvgBuf[ n ] = '\0';
  Dirty = 1;

  return 0;
}
