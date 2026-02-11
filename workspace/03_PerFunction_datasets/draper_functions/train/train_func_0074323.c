_x11_elm_drop_target_add(Evas_Object *obj, Elm_Sel_Type format,
                         Elm_Drop_Cb dropcb, void *cbdata)
{
   Dropable *drop;
   Ecore_X_Window xwin = _x11_elm_widget_xwin_get(obj);
   Eina_List *item;
   int first;

   _x11_elm_cnp_init();


   first = (!drops) ? 1 : 0;

   EINA_LIST_FOREACH(drops, item, drop)
     {
        if (drop->obj == obj)
          {

             drop->dropcb = dropcb;
             drop->cbdata = cbdata;
             drop->types = format;
             return EINA_TRUE;
          }
     }


   drop = calloc(1, sizeof(Dropable));
   if (!drop) return EINA_FALSE;

   drops = eina_list_append(drops, drop);

   if (!drops)
     {
        free(drop);
        return EINA_FALSE;
     }
   drop->dropcb = dropcb;
   drop->cbdata = cbdata;
   drop->types = format;
   drop->obj = obj;

   evas_object_event_callback_add(obj, EVAS_CALLBACK_DEL,

                                  (Evas_Object_Event_Cb)elm_drop_target_del,
                                  obj);


   if (!first) return EINA_TRUE;

   ecore_x_dnd_aware_set(xwin, EINA_TRUE);

   cnp_debug("Adding drop target calls xwin=%#llx\n", (unsigned long long)xwin);
   handler_enter = ecore_event_handler_add(ECORE_X_EVENT_XDND_ENTER,
                                           _x11_dnd_enter, NULL);
   handler_pos = ecore_event_handler_add(ECORE_X_EVENT_XDND_POSITION,
                                         _x11_dnd_position, NULL);
   handler_drop = ecore_event_handler_add(ECORE_X_EVENT_XDND_DROP,
                                          _x11_dnd_drop, NULL);
   return EINA_TRUE;
}
