days_per_month(int calendar, int year, int month)
{
  int dayspermonth = 0;
  int *dpm = NULL;
  int dpy;

  dpy = calendar_dpy(calendar);

  if      ( dpy == 360 ) dpm = month_360;
  else if ( dpy == 365 ) dpm = month_365;
  else                   dpm = month_366;

  if ( month >= 1 && month <= 12 )
    dayspermonth = dpm[month-1];


  if ( dpy == 0 && month == 2 )
    {
      if ( (year%4 == 0 && year%100 != 0) || year%400 == 0 )
	dayspermonth = 29;
      else
	dayspermonth = 28;
    }

  return (dayspermonth);
}
