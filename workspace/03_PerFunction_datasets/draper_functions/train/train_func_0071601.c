update_logfile( const int odes, const bool force,
                              const bool retry )
  {
  if( !filename_ ) return true;
  const int interval = 30 + std::min( 270, sblocks() / 38 );
  const long t2 = std::time( 0 );
  if( !force && t2 - ul_t1 < interval ) return true;
  ul_t1 = t2;
  if( odes >= 0 ) fsync( odes );

  errno = 0;
  FILE * const f = std::fopen( filename_, "w" );
  if( f )
    {
    write_logfile( f );
    if( std::fclose( f ) == 0 ) return true;
    }

  if( verbosity >= 0 )
    {
    char buf[80];
    snprintf( buf, sizeof buf, f ? "Error writing logfile '%s'." :
                                   "Error opening logfile '%s' for writing.",
              filename_ );
    if( retry ) std::fprintf( stderr, "\n" );
    show_error( buf, errno );
    if( retry )
      {
      std::fprintf( stderr, "Fix the problem and press ENTER to retry, or Q+ENTER to abort. " );
      std::fflush( stderr );
      while( true )
        {
        const char c = std::tolower( std::fgetc( stdin ) );
        if( c == '\r' || c == '\n' )
          {
          std::fprintf( stderr, "\n\n\n\n" );
          return update_logfile( -1, true );
          }
        if( c == 'q' ) break;
        }
      }
    }
  return false;
  }
