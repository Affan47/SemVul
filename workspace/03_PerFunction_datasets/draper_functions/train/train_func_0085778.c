dayofyear(int calendar, int vdate, int vtime)
{
  int month_360[12] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
  int month_365[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int month_366[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int *dpm;
  int im, dpy;
  int year, month, day;
  int hour, minute, second;
  double doy = 0;

  cdiDecodeDate(vdate, &year, &month, &day);
  cdiDecodeTime(vtime, &hour, &minute, &second);

  dpy = days_per_year(calendar, year);

  for ( im = 1; im < month; ++im )
    {
      if      ( dpy == 360 ) dpm = month_360;
      else if ( dpy == 365 ) dpm = month_365;
      else                   dpm = month_366;

      if ( im >= 1 && im <= 12 ) doy += dpm[im-1];
    }

  doy += (day-1);
  doy += (second+minute*60+hour*3600)/86400.;

  if ( cdoVerbose )
    cdoPrint("%d %d %d %g\n", vdate, vtime, dpy, doy);

  return (doy);
}
