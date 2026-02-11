_ecore_evas_obj_callback_changed_size_hints(void *data, Evas *e __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
   Ecore_Evas *ee = data;
   Evas_Coord w, h;

   evas_object_size_hint_min_get(obj, &w, &h);
   ecore_evas_size_min_set(ee, w, h);

   evas_object_size_hint_max_get(obj, &w, &h);
   if (w < 1) w = -1;
   if (h < 1) h = -1;
   ecore_evas_size_max_set(ee, w, h);
}
