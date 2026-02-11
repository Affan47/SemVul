gregorianToJD(int32_t year, int32_t month, int32_t date) {
   double julianDay = (JULIAN_EPOCH - 1) +
      (365 * (year - 1)) +
      uprv_floor((year - 1) / 4) +
      (-uprv_floor((year - 1) / 100)) +
      uprv_floor((year - 1) / 400) +
      uprv_floor((((367 * month) - 362) / 12) +
            ((month <= 2) ? 0 :
             (isGregorianLeap(year) ? -1 : -2)
            ) +
            date);

   return julianDay;
}
