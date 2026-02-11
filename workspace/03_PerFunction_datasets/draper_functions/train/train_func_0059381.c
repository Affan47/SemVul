_list_new(Evas_Object *obj)
{
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd) return;

   wd->tbl = elm_table_add(obj);
   elm_object_part_content_set(wd->base, "elm.swallow.content", wd->tbl);
   evas_object_size_hint_weight_set(wd->tbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(wd->tbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(wd->tbl);

   wd->spacer = evas_object_rectangle_add(evas_object_evas_get(obj));
   evas_object_color_set(wd->spacer, 0, 0, 0, 0);
   elm_table_pack(wd->tbl, wd->spacer, 0, 0, 1, 1);


   wd->scr = elm_scroller_add(obj);
   elm_scroller_content_min_limit(wd->scr, EINA_TRUE, EINA_FALSE);
   elm_scroller_bounce_set(wd->scr, EINA_FALSE, EINA_TRUE);
   evas_object_size_hint_weight_set(wd->scr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(wd->scr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_event_callback_add(wd->scr,
                                  EVAS_CALLBACK_CHANGED_SIZE_HINTS,
                                  _changed_size_hints, obj);
   elm_table_pack(wd->tbl, wd->scr, 0, 0, 1, 1);
   evas_object_show(wd->scr);


   wd->box = elm_box_add(obj);
   evas_object_size_hint_weight_set(wd->box, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(wd->box, EVAS_HINT_FILL, 0.0);
   elm_object_content_set(wd->scr, wd->box);
   evas_object_show(wd->box);
}
