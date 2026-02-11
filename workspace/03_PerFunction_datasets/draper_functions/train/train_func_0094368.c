_resize_cb(void *data, Evas *evas __UNUSED__, Evas_Object *obj __UNUSED__, void *event __UNUSED__)
{
   Widget_Data *wd = elm_widget_data_get(data);
   Evas_Coord w, h;

   if (!wd) return;
   evas_object_geometry_get(wd->box, NULL, NULL, &w, &h);

   if (wd->h_box < h) evas_object_smart_callback_call(data, SIG_EXPANDED, NULL);
   else if (wd->h_box > h)
     evas_object_smart_callback_call(data, SIG_CONTRACTED, NULL);

   wd->w_box = w;
   wd->h_box = h;

   _view_update(data);
}
