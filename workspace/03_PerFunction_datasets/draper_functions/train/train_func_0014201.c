setInputFiles( int argc, char* argv [] )
{
  int i,j;

  if( (i = findArg( DATAINPUTSHORT, DATAINPUTLONG, argc, argv )) && (i + 1 < argc) &&
      access( argv[i+1], R_OK ) == 0 )
    dataTypesFile = fopen( argv[i+1], "rb" );


  for( j=1;j<argc;j++ )
    {
      if( ((dataTypesFile != NULL && i+1 != j) || (!dataTypesFile)) && access( argv[j], R_OK ) == 0 )
	dataFile = fopen( argv[j], "rb" );
    }
  if( dataFile == NULL )
    dataFile = stdin;
}
