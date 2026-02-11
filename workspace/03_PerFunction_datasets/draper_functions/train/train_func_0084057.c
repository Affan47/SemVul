_elm_dayselector_smart_content_set(Evas_Object *obj,
                                   const char *item,
                                   Evas_Object *content)
{
   int day;
   char buf[1024];
   Elm_Dayselector_Item *it = NULL;

   ELM_DAYSELECTOR_DATA_GET(obj, sd);

   if (strcmp(elm_object_widget_type_get(content), "elm_check"))
     return EINA_FALSE;

   if (!item) return EINA_FALSE;

   day = atoi(item + (strlen(item) - 1));
   if (day < 0 || day > ELM_DAYSELECTOR_MAX) return EINA_FALSE;

   it = _item_find(obj, day);
   if (it)
     {
        snprintf(buf, sizeof(buf), "day%d", _item_location_get(sd, it));

        if (!ELM_CONTAINER_CLASS(_elm_dayselector_parent_sc)->content_set
              (obj, buf, content))
          return EINA_FALSE;

        if (!content) return EINA_TRUE;


        evas_object_del(VIEW(it));
        VIEW(it) = content;
     }
   else
     {
        it = elm_widget_item_new(obj, Elm_Dayselector_Item);
        it->day = day;

        snprintf(buf, sizeof(buf), "day%d", _item_location_get(sd, it));

        if (!ELM_CONTAINER_CLASS(_elm_dayselector_parent_sc)->content_set
              (obj, buf, content))
          {
             elm_widget_item_free(it);
             return EINA_FALSE;
          }

        sd->items = eina_list_append(sd->items, it);
        VIEW(it) = content;
     }

   snprintf(buf, sizeof(buf), "day%d,visible", _item_location_get(sd, it));
   elm_layout_signal_emit(obj, buf, "elm");

   evas_object_smart_callback_add(VIEW(it), "changed", _item_clicked_cb, it);
   evas_object_event_callback_add
     (VIEW(it), EVAS_CALLBACK_DEL, _item_del_cb, obj);

   elm_object_signal_callback_add
     (VIEW(it), ITEM_TYPE_WEEKDAY_DEFAULT, "", _item_signal_emit_cb, it);
   elm_object_signal_callback_add
     (VIEW(it), ITEM_TYPE_WEEKDAY_STYLE1, "", _item_signal_emit_cb, it);
   elm_object_signal_callback_add
     (VIEW(it), ITEM_TYPE_WEEKEND_DEFAULT, "", _item_signal_emit_cb, it);
   elm_object_signal_callback_add
     (VIEW(it), ITEM_TYPE_WEEKEND_STYLE1, "", _item_signal_emit_cb, it);

   elm_layout_sizing_eval(obj);
   _update_items(obj);

   return EINA_TRUE;
}
