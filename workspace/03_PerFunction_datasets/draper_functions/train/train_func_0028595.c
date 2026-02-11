_e_smart_monitor_frame_cb_resize_start(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   Evas_Object *mon;
   E_Smart_Data *sd;


   if (!(mon = data)) return;
   if (!(sd = evas_object_smart_data_get(mon))) return;


   evas_pointer_canvas_xy_get(sd->evas, &sd->resize.x, &sd->resize.y);


   e_layout_child_geometry_get(mon, NULL, NULL,
                               &sd->current.w, &sd->current.h);


   e_layout_child_raise(mon);


   sd->resizing = EINA_TRUE;
}
