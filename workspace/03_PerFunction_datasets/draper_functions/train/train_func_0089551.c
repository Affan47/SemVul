days2mdhms
        (
          int year, double days,
          int& mon, int& day, int& hr, int& minute, double& sec
        )
   {
     int i, inttemp, dayofyr;
     double    temp;
     int lmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

     dayofyr = (int)floor(days);

     if ( (year % 4) == 0 )
       lmonth[1] = 29;

     i = 1;
     inttemp = 0;
     while ((dayofyr > inttemp + lmonth[i-1]) && (i < 12))
     {
       inttemp = inttemp + lmonth[i-1];
       i++;
     }
     mon = i;
     day = dayofyr - inttemp;


     temp = (days - dayofyr) * 24.0;
     hr   = (int)floor(temp);
     temp = (temp - hr) * 60.0;
     minute  = (int)floor(temp);
     sec  = (temp - minute) * 60.0;
   }
