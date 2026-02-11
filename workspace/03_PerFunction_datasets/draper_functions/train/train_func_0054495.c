cdiDecodeTimevalue(int timeunit, double timevalue, int *days, int *secs)
{
  static int lwarn = TRUE;

  if ( timeunit == TUNIT_MINUTE )
    {
      timevalue *= 60;
      timeunit = TUNIT_SECOND;
    }
  else if ( timeunit == TUNIT_HOUR )
    {
      timevalue /= 24;
      timeunit = TUNIT_DAY;
    }

  if ( timeunit == TUNIT_SECOND )
    {
      *days = (int) (timevalue/86400);
      *secs = (int) (timevalue - *days*86400.);
      if ( *secs < 0 ) { *days -= 1; *secs += 86400; };


    }
  else if ( timeunit == TUNIT_DAY )
    {
      *days = (int) timevalue;
      *secs = (int) ((timevalue - *days)*86400 + 0.5);
      if ( *secs < 0 ) { *days -= 1; *secs += 86400; };


    }
  else
    {
      if ( lwarn )
	{
	  Warning("timeunit %s unsupported!", tunitNamePtr(timeunit));
	  lwarn = FALSE;
	}
    }
}
