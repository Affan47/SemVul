e_smart_randr_monitor_add(Evas_Object *obj, Evas_Object *mon)
{
   E_Smart_Data *sd;


   if (!(sd = evas_object_smart_data_get(obj))) return;


   evas_object_smart_callback_add(mon, "monitor_moving",
                                  _e_smart_randr_monitor_cb_moving, obj);
   evas_object_smart_callback_add(mon, "monitor_moved",
                                  _e_smart_randr_monitor_cb_moved, obj);
   evas_object_smart_callback_add(mon, "monitor_resized",
                                  _e_smart_randr_monitor_cb_resized, obj);
   evas_object_smart_callback_add(mon, "monitor_rotated",
                                  _e_smart_randr_monitor_cb_rotated, obj);
   evas_object_smart_callback_add(mon, "monitor_changed",
                                  _e_smart_randr_monitor_cb_changed, obj);


   evas_object_event_callback_add(mon, EVAS_CALLBACK_DEL,
                                  _e_smart_randr_monitor_cb_deleted, NULL);


   e_layout_pack(sd->o_layout, mon);


   sd->monitors = eina_list_append(sd->monitors, mon);


   evas_object_show(mon);
}
