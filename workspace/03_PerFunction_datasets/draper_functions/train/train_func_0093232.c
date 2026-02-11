appointment_on_day_list(int mon, int year, int *mask,
                            int category, int datebook_version)
{
   struct tm tm_dom;
   CalendarEventList *tcel, *cel;
   int dow, ndim;
   int bit;
   int show_priv;
   int skip_privates;

   memset(&tm_dom, 0, sizeof(tm_dom));
   tm_dom.tm_hour=11;
   tm_dom.tm_mday=1;
   tm_dom.tm_mon=mon;
   tm_dom.tm_year=year;

   cel = NULL;


   if (datebook_version) {

      get_days_calendar_events2(&cel, NULL, 2, 2, 1, category, NULL);
   } else {
      get_days_calendar_events2(&cel, NULL, 2, 2, 1, CATEGORY_ALL, NULL);
   }

   show_priv = show_privates(GET_PRIVATES);
   skip_privates = (show_priv==HIDE_PRIVATES);

   get_month_info(mon, 1, year, &dow, &ndim);

   *mask = 0;

   weed_calendar_event_list(&cel, mon, year, skip_privates, mask);

   for (tm_dom.tm_mday=1, bit=1; tm_dom.tm_mday<=ndim; tm_dom.tm_mday++, bit=bit<<1) {
      if (*mask & bit) {
         continue;
      }

      mktime(&tm_dom);
      for (tcel=cel; tcel; tcel = tcel->next) {
         if (calendar_isApptOnDate(&(tcel->mcale.cale), &tm_dom)) {
            *mask = *mask | bit;
            break;
         }
      }
   }
   free_CalendarEventList(&cel);

   return EXIT_SUCCESS;
}
