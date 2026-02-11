match_facility(UPSINFO *ups, int offset,
   const GENINFO *junk, const char *v)
{
   const struct {
      const char *fn;
      int fi;
   } facnames[] = {
      {"daemon", LOG_DAEMON},
      {"local0", LOG_LOCAL0},
      {"local1", LOG_LOCAL1},
      {"local2", LOG_LOCAL2},
      {"local3", LOG_LOCAL3},
      {"local4", LOG_LOCAL4},
      {"local5", LOG_LOCAL5},
      {"local6", LOG_LOCAL6},
      {"local7", LOG_LOCAL7},
      {"lpr", LOG_LPR},
      {"mail", LOG_MAIL},
      {"news", LOG_NEWS},
      {"uucp", LOG_UUCP},
      {"user", LOG_USER},
      {NULL, -1}
   };
   int i;
   char x[MAXSTRING];
   int oldfac;

   if (!sscanf(v, "%s", x))
      return FAILURE;

   oldfac = ups->sysfac;
   for (i = 0; facnames[i].fn; i++) {
      if (!(strcasecmp(facnames[i].fn, x))) {
         ups->sysfac = facnames[i].fi;

         if (ups->sysfac != oldfac) {
            closelog();
            openlog("apcupsd", LOG_CONS | LOG_PID, ups->sysfac);
         }
         return SUCCESS;
      }
   }

   return FAILURE;
}
