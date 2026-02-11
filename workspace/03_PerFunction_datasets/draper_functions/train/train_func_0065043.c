decode_julday(int calendar,
		   int julday,
		   int *year,
		   int *mon,
		   int *day)
{
  int a = julday;
  double b, c;
  double d, e, f;

  b = floor((a - 1867216.25)/36524.25);
  c = a + b - floor(b/4) + 1525;

  if ( calendar == CALENDAR_STANDARD )
    if ( a < 2299161 )
      {
	c = a + 1524;
      }

  d = floor((c - 122.1)/365.25);
  e = floor(365.25*d);
  f = floor((c - e)/30.6001);

  *day  = (int)(c - e - floor(30.6001*f));
  *mon  = (int)(f - 1 - 12*floor(f/14));
  *year = (int)(d - 4715 - floor((7 + *mon)/10));
}
