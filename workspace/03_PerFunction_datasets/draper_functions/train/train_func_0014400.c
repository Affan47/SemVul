_ecore_event_filters_apply()
{
   if (!event_filter_current)
     {

         event_filter_current = event_filters;
     }
   else
     {

         event_filter_current = (Ecore_Event_Filter *)EINA_INLIST_GET(event_filter_current)->next;
     }

   while (event_filter_current)
     {
        Ecore_Event_Filter *ef = event_filter_current;

        if (!ef->delete_me)
          {
             ef->references++;

             if (ef->func_start)
               ef->loop_data = _ecore_call_data_cb(ef->func_start, ef->data);

             if (!event_filter_event_current)
               {

                   event_filter_event_current = events;
               }
             else
               {

                   event_filter_event_current = (Ecore_Event *)EINA_INLIST_GET(event_filter_event_current)->next;
               }

             while (event_filter_event_current)
               {
                  Ecore_Event *e = event_filter_event_current;

                  if (!_ecore_call_filter_cb(ef->func_filter, ef->data,
                                             ef->loop_data, e->type, e->event))
                    {
                       ecore_event_del(e);
                    }

                  if (event_filter_event_current)
                    event_filter_event_current = (Ecore_Event *)EINA_INLIST_GET(event_filter_event_current)->next;
               }
             if (ef->func_end)
               _ecore_call_end_cb(ef->func_end, ef->data, ef->loop_data);

             ef->references--;
          }

        if (event_filter_current)
          event_filter_current = (Ecore_Event_Filter *)EINA_INLIST_GET(event_filter_current)->next;
     }
   if (event_filters_delete_me)
     {
        int deleted_in_use = 0;
        Ecore_Event_Filter *l;
        for (l = event_filters; l; )
          {
             Ecore_Event_Filter *ef = l;
             l = (Ecore_Event_Filter *)EINA_INLIST_GET(l)->next;
             if (ef->delete_me)
               {
                  if (ef->references)
                    {
                       deleted_in_use++;
                       continue;
                    }

                  event_filters = (Ecore_Event_Filter *)eina_inlist_remove(EINA_INLIST_GET(event_filters), EINA_INLIST_GET(ef));
                  ECORE_MAGIC_SET(ef, ECORE_MAGIC_NONE);
                  ecore_event_filter_mp_free(ef);
               }
          }
        if (!deleted_in_use)
          event_filters_delete_me = 0;
     }
}
