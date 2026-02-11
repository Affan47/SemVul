Calendar_Date(double jd, struct tm *cdate)
{

  int Z,month;
  double A,B,C,D,E,F,alpha,day,year,factor;

  factor = 0.5/secday/1000;
  F = Frac(jd + 0.5);
  if (F + factor >= 1.0)
    {
      jd = jd + factor;
      F  = 0.0;
    }
  Z = Round(jd);
  if( Z < 2299161 )
    A = Z;
  else
    {
      alpha = Int((Z - 1867216.25)/36524.25);
      A = Z + 1 + alpha - Int(alpha/4);
    }
  B = A + 1524;
  C = Int((B - 122.1)/365.25);
  D = Int(365.25 * C);
  E = Int((B - D)/30.6001);
  day = B - D - Int(30.6001 * E) + F;

  if( E < 13.5 )
    month = Round(E - 1);
  else
    month = Round(E - 13);
  if( month > 2.5 )
    year = C - 4716;
  else
    year = C - 4715;

  cdate->tm_year = (int) year;
  cdate->tm_mon = month;
  cdate->tm_mday = (int) floor(day);

}
