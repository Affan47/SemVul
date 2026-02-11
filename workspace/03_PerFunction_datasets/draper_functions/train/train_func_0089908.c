status_write(UPSINFO *ups, const char *fmt, ...)
{
   va_list ap;
   int i;
   char buf[MAXSTRING];

   va_start(ap, fmt);
   avsnprintf(buf, sizeof(buf), fmt, ap);
   va_end(ap);

   if ((i = (strlen(largebuf) + strlen(buf))) < (int)(sizeof(largebuf) - 1)) {
      astrncat(largebuf, buf, sizeof(largebuf));
      stat_recs++;
   } else {
      log_event(ups, LOG_ERR,
         "apcserver.c: Status buffer overflow %d bytes\n", i - sizeof(largebuf));
   }
}
