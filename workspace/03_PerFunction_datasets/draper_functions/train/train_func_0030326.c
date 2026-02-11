main( int argc, char **argv )
{
  FILE *f;

  progname = argv[0];

  if( argc < 2 ) {
    fprintf( stderr, "Usage: %s <testsfile>\n", progname );
    return 1;
  }

  testsfile = argv[1];

  if( init_dummies() ) return 1;


  z80_init();

  f = fopen( testsfile, "r" );
  if( !f ) {
    fprintf( stderr, "%s: couldn't open tests file `%s': %s\n", progname,
	     testsfile, strerror( errno ) );
    return 1;
  }

  while( run_test( f ) ) {

  }

  if( fclose( f ) ) {
    fprintf( stderr, "%s: couldn't close `%s': %s\n", progname, testsfile,
	     strerror( errno ) );
    return 1;
  }

  return 0;
}
