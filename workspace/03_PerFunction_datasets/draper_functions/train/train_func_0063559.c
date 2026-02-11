elm_transit_go(Elm_Transit *transit)
{
   ELM_TRANSIT_CHECK_OR_RETURN(transit);

   Eina_List *elist;
   Evas_Object *obj;

   if (transit->animator)
     ecore_animator_del(transit->animator);

   EINA_LIST_FOREACH(transit->objs, elist, obj)
     _transit_obj_data_update(transit, obj);

   if (!transit->event_enabled)
     {
        EINA_LIST_FOREACH(transit->objs, elist, obj)
          evas_object_freeze_events_set(obj, EINA_TRUE);
     }

   transit->time.paused = 0;
   transit->time.delayed = 0;
   transit->time.begin = ecore_loop_time_get();
   transit->animator = ecore_animator_add(_transit_animate_cb, transit);
   _transit_animate_cb(transit);
}
