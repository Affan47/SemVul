Pp_show_msg( struct Pretty_print * const pp, const char * const msg )
  {
  if( pp->verbosity >= 0 )
    {
    if( pp->first_post )
      {
      int i, len;
      pp->first_post = false;
      fprintf( stderr, "  %s: ", pp->name );
      len = pp->longest_name - strlen( pp->name );
      for( i = 0; i < len; ++i ) fprintf( stderr, " " );
      if( !msg ) fflush( stderr );
      }
    if( msg ) fprintf( stderr, "%s.\n", msg );
    }
  }
