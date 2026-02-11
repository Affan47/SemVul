main(int argc, char *argv[])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];

  if( argc > 2 )
    {
    const char *outfilename = argv[2];
    fout = fopen( outfilename, "w" );
    }
  else
    {
    fout = stdout;
    }

  bool b;
  if( isjp2file( filename ) )
    {
    b = parsejp2( filename, &print2, &print );
    }
  else
    {
    b = parsej2k( filename, &print );
    }
  if( argc > 2 )
    {
    fclose( fout );
    }
  if( !b ) return 1;

  return 0;
}
