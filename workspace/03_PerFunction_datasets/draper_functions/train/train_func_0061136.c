elm_widget_focus_region_get(const Evas_Object *obj,
                            Evas_Coord        *x,
                            Evas_Coord        *y,
                            Evas_Coord        *w,
                            Evas_Coord        *h)
{
   Elm_Widget_Smart_Data *sd;

   if (!obj) return;

   sd = evas_object_smart_data_get(obj);
   if (!sd || !_elm_widget_is(obj) || !sd->on_focus_region)
     {
        evas_object_geometry_get(obj, NULL, NULL, w, h);
        if (x) *x = 0;
        if (y) *y = 0;
        return;
     }
   sd->on_focus_region(obj, x, y, w, h);
}
