tm_woy(time_t stime)
{
   int woy, fty, tm_yday;
   time_t time4;
   struct tm tm;

   memset(&tm, 0, sizeof(struct tm));
   (void)localtime_r(&stime, &tm);
   tm_yday = tm.tm_yday;
   tm.tm_mon = 0;
   tm.tm_mday = 4;
   tm.tm_isdst = 0;
   time4 = mktime(&tm);
   (void)localtime_r(&time4, &tm);
   fty = 1 - tm.tm_wday;
   if (fty <= 0) {
      fty += 7;
   }
   woy = tm_yday - fty + 4;
   if (woy < 0) {
      return 0;
   }
   return 1 + woy / 7;
}
