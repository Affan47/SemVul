init_msgfile(HSCPRC * hp, STRPTR fname)
{
   BOOL ok = TRUE;

   if (fname)
   {
      D(fprintf(stderr, DHSC "write msg to `%s'\n", fname));

      errno = 0;
      msgfile = fopen(fname, "w");
      if (!msgfile)
      {
#define MSGBUFLEN 79
         STRARR msgbuf[MSGBUFLEN + 1];

         strncpy(msgbuf, "unable to open message file `", MSGBUFLEN);
         strncat(msgbuf, fname, MSGBUFLEN - strlen(msgbuf));
         strncat(msgbuf, "': ", MSGBUFLEN - strlen(msgbuf));
         strncat(msgbuf, strerror(errno), MSGBUFLEN - strlen(msgbuf));
         status_error(msgbuf);
         ok = FALSE;
      }
   }
   else
   {
      msgfile = stderr;
      D(fprintf(stderr, DHSC "write msg to <stderr>\n"));
   }

   return (ok);
}
