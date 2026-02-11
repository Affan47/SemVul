print_time(struct timeval *tvp)
{
   char timeZoneBuf[32];
   char *retn = ArgusPrintTimeBuf, *ptr;
   struct tm *tm;

   bzero (timeZoneBuf, sizeof(timeZoneBuf));
   bzero (ArgusPrintTimeBuf, sizeof(ArgusPrintTimeBuf));

   if (ArgusPrintGMT) {
      if ((tm = gmtime ((time_t *)&tvp->tv_sec)) == NULL)
         return (NULL);
   } else {
      if ((tm = localtime ((time_t *)&tvp->tv_sec)) == NULL)
         return (NULL);
   }

   if (uflag)
      sprintf (retn, "%9d", (int) tvp->tv_sec);
   else
      if ((strftime ((char *) retn, 64, RaTimeFormat, tm)) == 0)
         ArgusLog (LOG_ERR, "print_time: format %s not supported.\n",
                               RaTimeFormat);
   if (pflag) {
      ptr = &retn[strlen(retn)];

      if ((RaFieldDelimiter != ' ') && (RaFieldDelimiter != '\0')) {
         if (uflag) {
            sprintf (ptr, ".%06d", (int) tvp->tv_usec);
            ptr[pflag + 1] = '\0';

         } else {
            sprintf (ptr, "%c0.%06d", RaFieldDelimiter, (int) tvp->tv_usec);
            ptr[pflag + 3] = '\0';
         }

      } else {
         sprintf (ptr, ".%06d", (int) tvp->tv_usec);
         ptr[pflag + 1] = '\0';
      }
   }

   return (retn);
}
