show_header( const File_header header )
  {
  const char * const prefix[8] =
    { "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi", "Yi" };
  enum { factor = 1024 };
  const char * p = "";
  const char * np = "  ";
  unsigned num = Fh_get_dictionary_size( header ), i;
  bool exact = ( num % factor == 0 );

  for( i = 0; i < 8 && ( num > 9999 || ( exact && num >= factor ) ); ++i )
    { num /= factor; if( num % factor != 0 ) exact = false;
      p = prefix[i]; np = ""; }
  fprintf( stderr, "version %d, dictionary size %s%4u %sB.  ",
           Fh_version( header ), np, num, p );
  }
