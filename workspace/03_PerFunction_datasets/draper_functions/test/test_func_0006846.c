getCdoPath()
{
  char *cdoPath = getenv("CDO_PATH");

  if ( cdoPath == NULL )
    {
      struct stat filestat;
      int status;
      status = stat("$HOME/bin/cdo", &filestat);
      if ( status == 0 )
	return "$HOME/bin/cdo";
      else
	{
	  fprintf(stderr, "cdo binary not found! Use CDO_PATH to set the path to cdo.\n");
	  exit(-1);
	}
    }

  return cdoPath;
}
