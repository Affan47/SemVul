IndianToJD(int32_t year, int32_t month, int32_t date) {
   int32_t leapMonth, gyear, m;
   double start, jd;

   gyear = year + INDIAN_ERA_START;


   if(isGregorianLeap(gyear)) {
      leapMonth = 31;
      start = gregorianToJD(gyear, 3, 21);
   }
   else {
      leapMonth = 30;
      start = gregorianToJD(gyear, 3, 22);
   }

   if (month == 1) {
      jd = start + (date - 1);
   } else {
      jd = start + leapMonth;
      m = month - 2;


      if (m > 5) {
          m = 5;
      }

      jd += m * 31;

      if (month >= 8) {
         m = month - 7;
         jd += m * 30;
      }
      jd += date - 1;
   }

   return jd;
}
