next_filename( void )
  {
  const unsigned len = strlen( known_extensions[0].from );
  int i, j;

  if( strlen( output_filename ) >= len + 5 )
    for( i = strlen( output_filename ) - len - 1, j = 0; j < 5; --i, ++j )
      {
      if( output_filename[i] < '9' ) { ++output_filename[i]; return true; }
      else output_filename[i] = '0';
      }
  return false;
  }
