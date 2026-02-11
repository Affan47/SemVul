_item_new(Evas_Object *obj)
{
   Elm_Color_Item *item;

   item = elm_widget_item_new(obj, Elm_Color_Item);
   if (!item) return NULL;

   VIEW(item) = elm_layout_add(obj);
   elm_layout_theme_set
     (VIEW(item), "colorselector", "item", elm_widget_style_get(obj));
   evas_object_size_hint_weight_set
     (VIEW(item), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(VIEW(item), EVAS_HINT_FILL, EVAS_HINT_FILL);

   item->color_obj = edje_object_add(evas_object_evas_get(obj));
   elm_widget_theme_object_set
     (obj, item->color_obj, "colorselector", "item/color",
     elm_widget_style_get(obj));
   evas_object_size_hint_weight_set
     (item->color_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set
     (item->color_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_event_callback_add
     (item->color_obj, EVAS_CALLBACK_MOUSE_DOWN, _on_color_pressed, item);
   evas_object_event_callback_add
     (item->color_obj, EVAS_CALLBACK_MOUSE_UP, _on_color_released, item);
   elm_object_part_content_set(VIEW(item), "color_obj", item->color_obj);

   _item_sizing_eval(item);
   evas_object_show(VIEW(item));


   if (_elm_config->access_mode == ELM_ACCESS_MODE_ON)
     _access_widget_item_register(item);

   return item;
}
