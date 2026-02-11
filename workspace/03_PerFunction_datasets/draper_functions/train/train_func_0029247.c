append_anni_years(char *desc, int max, struct tm *date,
                       struct Appointment *appt, struct CalendarEvent *cale)
{
   int len;
   int year;


   if ((!appt) && (!cale)) {
      return;
   }
   if ((appt) && (appt->repeatType != repeatYearly))
      return;
   if ((cale) && (cale->repeatType != repeatYearly))
      return;


   if (!get_pref_int_default(PREF_DATEBOOK_ANNI_YEARS, FALSE))
      return;

   len = strlen(desc);


   if (len < 4 || len > (max - 7))
      return;


   year = strtoul(&desc[len - 4], NULL, 10);


   if (year < 1100 || year > 3000)
      return;


   sprintf(&desc[len], " (%d)", 1900 + date->tm_year - year);
}
