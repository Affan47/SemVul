get_season_start(void)
{
  int season_start = START_DEC;
  char *envstr;

  envstr = getenv("CDO_SEASON_START");
  if ( envstr )
    {
      if      ( strcmp(envstr, "DEC") == 0 ) season_start = START_DEC;
      else if ( strcmp(envstr, "JAN") == 0 ) season_start = START_JAN;

      if ( cdoVerbose )
	{
	  if      ( season_start == START_DEC )
	    cdoPrint("Set SEASON_START to December");
	  else if ( season_start == START_JAN )
	    cdoPrint("Set SEASON_START to January");
	}
    }

  return (season_start);
}
