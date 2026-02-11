_e_zone_cb_bg_mouse_up(void            *data,
                       Evas *evas       __UNUSED__,
                       Evas_Object *obj __UNUSED__,
                       void *event_info __UNUSED__)
{
   E_Zone *zone;

   zone = data;
   if (zone->cur_mouse_action)
     {
        if (ecore_event_current_type_get() == ECORE_EVENT_MOUSE_BUTTON_UP)
          {
             Ecore_Event_Mouse_Button *ev2;

             ev2 = ecore_event_current_event_get();
             if (zone->cur_mouse_action->func.end_mouse)
               zone->cur_mouse_action->func.end_mouse(E_OBJECT(zone), "", ev2);
             else if (zone->cur_mouse_action->func.end)
               zone->cur_mouse_action->func.end(E_OBJECT(zone), "");
          }
        e_object_unref(E_OBJECT(zone->cur_mouse_action));
        zone->cur_mouse_action = NULL;
     }
   else
     {
        if (ecore_event_current_type_get() == ECORE_EVENT_MOUSE_BUTTON_UP)
          {
             Ecore_Event_Mouse_Button *ev2;

             ev2 = ecore_event_current_event_get();
             e_bindings_mouse_up_event_handle(E_BINDING_CONTEXT_ZONE,
                                              E_OBJECT(zone), ev2);
          }
     }
}
