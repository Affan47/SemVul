copy_calendarEvent_to_appointment(const struct CalendarEvent *cale,
                                      struct Appointment *appt)
{
   int i;

   appt->event = cale->event;
   appt->begin = cale->begin;
   appt->end = cale->end;
   appt->alarm = cale->alarm;
   appt->advance = cale->advance;
   appt->advanceUnits = cale->advanceUnits;
   appt->repeatType = cale->repeatType;
   appt->repeatForever = cale->repeatForever;
   appt->repeatEnd = cale->repeatEnd;
   appt->repeatFrequency = cale->repeatFrequency;
   appt->repeatDay = cale->repeatDay;
   for (i=0; i<7; i++) {
      appt->repeatDays[i] = cale->repeatDays[i];
   }
   appt->repeatWeekstart = cale->repeatWeekstart;
   appt->exceptions = cale->exceptions;
   if (cale->exceptions > 0) {
      appt->exception = (struct tm *) malloc(cale->exceptions * sizeof(struct tm));
      memcpy(appt->exception, cale->exception, cale->exceptions * sizeof(struct tm));
   } else {
      appt->exception = NULL;
   }
   if (cale->description) {
      appt->description = strdup(cale->description);
   } else {
      appt->description = NULL;
   }
   if (cale->note) {
      appt->note = strdup(cale->note);
   } else {
      appt->note = NULL;
   }

   return EXIT_SUCCESS;
}
