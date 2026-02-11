ArgusPrintDuration (char *date, struct ArgusRecord *ptr)
{
   char *sptr, *iptr, delim = ' ';
   struct timeval *start = NULL, *last = NULL;
   struct timeval  buf,  *time = &buf;

   if (ptr->ahdr.type & ARGUS_MAR) {
      start = &ptr->argus_mar.startime;
      last  = &ptr->argus_mar.now;

   } else {
      start = &ptr->argus_far.time.start;
      last  = &ptr->argus_far.time.last;
   }

   *time = *last;
   time->tv_sec  -= start->tv_sec;
   time->tv_usec -= start->tv_usec;

   if (time->tv_usec < 0) {
      time->tv_sec--;
      time->tv_usec += 1000000;
   }

   if (time->tv_usec >= 1000000) {
      time->tv_sec++;
      time->tv_usec -= 1000000;
   }

   iptr = &date[strlen(date)];
   sptr = &date[strlen(date)];

   if ((RaFieldDelimiter != ' ') && (RaFieldDelimiter != '\0'))
      sprintf(sptr, "%u", (unsigned int) time->tv_sec);
   else
      sprintf(sptr, "%8u", (unsigned int) time->tv_sec);

   if (pflag) {
      sptr = &date[strlen(date)];
      sprintf(sptr, ".%06d", (int) time->tv_usec);
      sptr[pflag + 1] = '\0';
   }

   if ((RaFieldDelimiter != ' ') && (RaFieldDelimiter != '\0'))
      sprintf(&date[strlen(date)], "%c", delim);
   else
      sprintf(&date[strlen(date)], "%c", ' ');
}
