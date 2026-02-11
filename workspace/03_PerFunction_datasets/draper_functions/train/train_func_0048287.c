StrToTime(const string &Val,time_t &Result)
{
   struct tm Tm;
   char Month[10];


   const char *I = strchr(Val.c_str(), ' ');


   Month[0] = 0;
   if (sscanf(I," %2d %3s %4d %2d:%2d:%2d GMT",&Tm.tm_mday,Month,&Tm.tm_year,
	      &Tm.tm_hour,&Tm.tm_min,&Tm.tm_sec) != 6)
   {

      if (sscanf(I," %2d-%3s-%3d %2d:%2d:%2d GMT",&Tm.tm_mday,Month,
		 &Tm.tm_year,&Tm.tm_hour,&Tm.tm_min,&Tm.tm_sec) == 6)
	 Tm.tm_year += 1900;
      else
      {

	 if (sscanf(I," %3s %2d %2d:%2d:%2d %4d",Month,&Tm.tm_mday,
		    &Tm.tm_hour,&Tm.tm_min,&Tm.tm_sec,&Tm.tm_year) != 6)
	 {

	    if (sscanf(Val.c_str(),"%4d%2d%2d%2d%2d%2d",&Tm.tm_year,&Tm.tm_mon,
		       &Tm.tm_mday,&Tm.tm_hour,&Tm.tm_min,&Tm.tm_sec) != 6)
	       return false;
	    Tm.tm_mon--;
	 }
      }
   }

   Tm.tm_isdst = 0;
   if (Month[0] != 0)
      Tm.tm_mon = MonthConv(Month);
   else
      Tm.tm_mon = 0;
   Tm.tm_year -= 1900;


   Result = timegm(&Tm);
   return true;
}
