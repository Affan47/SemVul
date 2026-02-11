sighup_handler( int signum )
  {
  if( signum ) {}
  if( mutex ) sighup_pending = true;
  else
    {
    const char hb[] = "ed.hup";
    sighup_pending = false;
    if( last_addr() && modified() &&
        write_file( hb, "w", 1, last_addr() ) < 0 )
      {
      char * const s = getenv( "HOME" );
      const int len = ( s ? strlen( s ) : 0 );
      const int need_slash = ( ( !len || s[len-1] != '/' ) ? 1 : 0 );
      char * const hup = ( ( len + need_slash + (int)sizeof hb < path_max( 0 ) ) ?
                    (char *) malloc( len + need_slash + sizeof hb ) : 0 );
      if( len && hup )
        {
        memcpy( hup, s, len );
        if( need_slash ) hup[len] = '/';
        memcpy( hup + len + need_slash, hb, sizeof hb );
        if( write_file( hup, "w", 1, last_addr() ) >= 0 ) exit( 0 );
        }
      exit( 1 );
      }
    exit( 0 );
    }
  }
