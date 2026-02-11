e_widget_image_add_from_object(Evas *evas, Evas_Object *object, int minw, int minh)
{
   Evas_Object *obj, *o;
   E_Widget_Data *wd;
   int mw = 0, mh = 0;

   obj = e_widget_add(evas);
   e_widget_del_hook_set(obj, _e_wid_del_hook);
   wd = calloc(1, sizeof(E_Widget_Data));

   evas_object_show(object);
   o = e_icon_add(evas);
   e_icon_fill_inside_set(o, 1);
   e_icon_edje_object_set(o, object);
   wd->img = o;
   e_widget_data_set(obj, wd);
   e_widget_can_focus_set(obj, 0);
   wd->minw = minw <= 0 ? minw : 0;
   wd->minh = minh <= 0 ? minh : 0;
   edje_object_size_min_get(object, &mw, &mh);
   if (minw || minh)
     e_widget_size_min_set(obj, minw, minh);
   else
     e_widget_size_min_set(obj, mw, mh);
   e_widget_sub_object_add(obj, o);
   e_widget_resize_object_set(obj, o);

   return obj;
}
