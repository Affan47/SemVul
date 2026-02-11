main( int argc, char** argv )
{
  int rc = 0;


  if( ( ExeName = strrchr( argv[0], '/' ) ) )
    ExeName++;
  else
    ExeName = argv[0];


  if( !readDataFile() )
    return 1;


  if( !readEnvironmentVars() )
    return 1;


  if( !parseCommandLine( argc, argv ) )
    return 1;


  if( Config.showme_flags == 0 || Config.showme_flags == SHOWME_FLAG_ALL )
  {
    rc = doWrap();
  }
  else
  {
    showFlags();
  }

  return rc;
}
