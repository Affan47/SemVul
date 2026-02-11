ArgusPrintLoad (char *buf, struct ArgusRecord *argus)
{
   int src_count = 0, dst_count = 0, src_bytes = 0, dst_bytes = 0;
   struct timeval *start = NULL, *last = NULL;
   struct timeval  timebuf,  *time = &timebuf;
   char tmpbuf[128], *ptr = tmpbuf;
   double seconds;

   start = &argus->argus_far.time.start;
   last  = &argus->argus_far.time.last;

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

   seconds = (double)(time->tv_sec * 1.0) + (double)(time->tv_usec/1000000.0);

   src_count = argus->argus_far.src.count;
   dst_count = argus->argus_far.dst.count;

   if (Aflag) {
      src_bytes = argus->argus_far.src.appbytes;
      dst_bytes = argus->argus_far.dst.appbytes;
   } else {
      src_bytes = argus->argus_far.src.bytes;
      dst_bytes = argus->argus_far.dst.bytes;
   }

   if (seconds) {
      sprintf (ptr, "%.2f", ((double)(src_bytes * 8.0))/seconds);
      sprintf (buf, "%13s", ptr);
      sprintf (ptr, "%.2f", ((double)(dst_bytes * 8.0))/seconds);
      sprintf (&buf[strlen(buf)], "%13s  ", ptr);
   } else {
      sprintf (ptr, "%.2f", 0.0);
      sprintf (buf, "%13s", ptr);
      sprintf (ptr, "%.2f", 0.0);
      sprintf (&buf[strlen(buf)], "%13s  ", ptr);
   }
}
