readAll ( char* buf, size_t len )
{
  int origLen = len;
  while ( len > 0 )
  {
    fd_set rfds;
    struct timeval tv;
    int retval;

    int tmp_sockfd = _sockfd;
    if ( tmp_sockfd == -1 ) {
      return -1;
    }


    FD_ZERO ( &rfds );
    FD_SET ( tmp_sockfd, &rfds );

    tv.tv_sec = 120;
    tv.tv_usec = 0;

    retval = jalib::select ( tmp_sockfd+1, &rfds, NULL, NULL, &tv );


    if ( retval == -1 )
    {
      if ( errno == EBADF ) {
        JWARNING (false) .Text ( "Socket already closed" );
        return -1;
      } else if( errno != EINTR ){
        JWARNING ( retval >= 0 )
          ( tmp_sockfd ) ( JASSERT_ERRNO ).Text ( "select() failed" );
        return -1;
      }
    }
    else if ( retval )
    {
      errno = 0;
      ssize_t cnt = read ( buf, len );
      if ( cnt < 0 && errno != EAGAIN && errno != EINTR )
      {
        JWARNING(cnt>=0)(sockfd())(cnt)(len)(JASSERT_ERRNO).Text( "JSocket read failure" );
        return -1;
      }
      if (cnt == 0)
      {
        JWARNING(cnt!=0)(sockfd())(origLen)(len).Text( "JSocket needed to read origLen chars,\n still needs to read len chars, but EOF reached" );
        return -1;
      }
      if ( cnt > 0 )
      {
        buf += cnt;
        len -= cnt;
      }
    }
    else
    {
      JTRACE ( "still waiting for data" ) ( tmp_sockfd ) ( len );
    }
  }
  return origLen;
}
