Months2Seconds(int m)

{
  static long days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  long tot_days = 0;
  int this_month,i,month,year;

if (m == 0)
   {
   return 0;
   }

this_month = Month2Int(VMONTH);
year = Str2Int(VYEAR);

for (i = 0; i < m; i++)
   {
   month = (this_month - i) % 12;

   while (month < 0)
      {
      month += 12;
      year--;
      }

   if ((year % 4) && (month == 1))
      {
      tot_days += 29;
      }
   else
      {
      tot_days += days[month];
      }
   }

return (long) tot_days * 3600 * 24;
}
