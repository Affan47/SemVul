qinstance_is_calendar_referenced(const lListElem *this_elem,
                                 const lListElem *calendar)
{
   bool ret = false;
   const char *queue_calendar = NULL;

   DENTER(TOP_LAYER, "qinstance_is_calendar_referenced");
   queue_calendar = lGetString(this_elem, QU_calendar);
   if (queue_calendar != NULL) {
      const char *calendar_name = lGetString(calendar, CAL_name);

      if (calendar_name && !strcmp(queue_calendar, calendar_name)) {
         ret = true;
      }
   }
   DRETURN(ret);
}
