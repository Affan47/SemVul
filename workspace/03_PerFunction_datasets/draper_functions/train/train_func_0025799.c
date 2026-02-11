read_logfile( const char * const logname,
                   std::vector< Sblock > & sblock_vector,
                   long long & current_pos, Logbook::Status & current_status )
  {
  FILE * const f = std::fopen( logname, "r" );
  if( !f ) return false;
  int linenum = 0;
  sblock_vector.clear();

  const char * line = my_fgets( f, linenum );
  if( line )
    {
    char ch;
    int n = std::sscanf( line, "%lli %c\n", &current_pos, &ch );
    if( n == 2 && current_pos >= 0 && Logbook::isstatus( ch ) )
      current_status = Logbook::Status( ch );
    else
      {
      show_logfile_error( logname, linenum );
      show_error( "Are you using a logfile from ddrescue 1.5 or older?" );
      std::exit( 2 );
      }

    while( true )
      {
      line = my_fgets( f, linenum );
      if( !line ) break;
      long long pos, size;
      n = std::sscanf( line, "%lli %lli %c\n", &pos, &size, &ch );
      if( n == 3 && pos >= 0 && Sblock::isstatus( ch ) &&
          ( size > 0 || size == -1 || ( size == 0 && pos == 0 ) ) )
        {
        const Sblock::Status st = Sblock::Status( ch );
        Sblock sb( pos, size, st ); sb.fix_size();
        if( sblock_vector.size() > 0 && !sb.follows( sblock_vector.back() ) )
          { show_logfile_error( logname, linenum ); std::exit( 2 ); }
        sblock_vector.push_back( sb );
        }
      else
        { show_logfile_error( logname, linenum ); std::exit( 2 ); }
      }
    }
  std::fclose( f );
  return true;
  }
