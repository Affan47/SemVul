_sizing_eval(Evas_Object *obj)
{
   Widget_Data *wd;
   Evas_Coord_Rectangle rect = { 0, 0, 1, 1 };
   Evas_Coord_Point list_size = { 0, 0 };

   wd = elm_widget_data_get(obj);
   if (!wd) return;


   wd->dir = _calc_base_geometry(obj, &rect);
   _update_arrow(obj, wd->dir, rect);
   _shift_base_by_arrow(wd->arrow, wd->dir, &rect);

   if ((wd->list) && (wd->list_visible))
     {
        evas_object_geometry_get(wd->list, 0, 0, &list_size.x, &list_size.y);
        if ((list_size.x >= rect.w) || (list_size.y >= rect.h))
          {
             elm_list_mode_set(wd->list, ELM_LIST_COMPRESS);
             evas_object_size_hint_min_set(wd->box, rect.w, rect.h);
             evas_object_size_hint_min_set(obj, rect.w, rect.h);
          }
   }

   evas_object_move(wd->base, rect.x, rect.y);
   evas_object_resize(wd->base, rect.w, rect.h);
   _show_signal_emit(obj, wd->dir);
}
