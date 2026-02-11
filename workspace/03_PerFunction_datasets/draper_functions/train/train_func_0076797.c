calendar_db3_hack_date(struct CalendarEvent *cale, struct tm *today)
{
   int t1, t2;

   if (today==NULL) {
      return EXIT_SUCCESS;
   }
   if (!cale->note) {
      return EXIT_SUCCESS;
   }
   if (strlen(cale->note) > 8) {
      if ((cale->note[0]=='#') && (cale->note[1]=='#')) {
         if (cale->note[2]=='f' || cale->note[2]=='F') {

            t1 = cale->begin.tm_mday + cale->begin.tm_mon*31 + cale->begin.tm_year*372;
            t2 = today->tm_mday + today->tm_mon*31 + today->tm_year*372;
            if (t1 > t2) return EXIT_SUCCESS;


            cale->begin.tm_mday = today->tm_mday;
            cale->begin.tm_mon = today->tm_mon;
            cale->begin.tm_year = today->tm_year;
            cale->begin.tm_wday = today->tm_wday;
            cale->begin.tm_yday = today->tm_yday;
            cale->begin.tm_isdst = today->tm_isdst;
            cale->end.tm_mday = today->tm_mday;
            cale->end.tm_mon = today->tm_mon;
            cale->end.tm_year = today->tm_year;
            cale->end.tm_wday = today->tm_wday;
            cale->end.tm_yday = today->tm_yday;
            cale->end.tm_isdst = today->tm_isdst;


            if (!(cale->repeatForever)) {
               if (compareTimesToDay(today, &(cale->repeatEnd))==1) {


                  memcpy(&(cale->begin), &(cale->repeatEnd), sizeof(struct tm));
                  memcpy(&(cale->end), &(cale->repeatEnd), sizeof(struct tm));
               }
            }
         }
      }
   }
   return EXIT_SUCCESS;
}
