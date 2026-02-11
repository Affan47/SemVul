days_per_year(int calendar, int year)
{
  int daysperyear;
  int dpy;

  dpy = calendar_dpy(calendar);

  if ( dpy == 0 )
    {
      if ( calendar == CALENDAR_STANDARD )
	{
	  if ( year == 1582 )
	    dpy = 355;
	  else if ( (year%4 == 0 && year%100 != 0) || year%400 == 0 )
	    dpy = 366;
	  else
	    dpy = 365;
	}
      else
	{
	  if ( (year%4 == 0 && year%100 != 0) || year%400 == 0 )
	    dpy = 366;
	  else
	    dpy = 365;
	}
    }

  daysperyear = dpy;

  return (daysperyear);
}
