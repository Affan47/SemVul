_content_set_hook(Evas_Object *obj, const char *part, Evas_Object *content)
{
   ELM_CHECK_WIDTYPE(obj, widtype);
   Evas_Coord min_w = -1, min_h = -1;
   Widget_Data *wd;
   if ((part) && (strcmp(part, "default"))) return;
   wd = elm_widget_data_get(obj);
   if ((!wd) || (!content)) return;
   if (content == wd->content) return;


   if (wd->content) evas_object_del(wd->content);


   wd->box = elm_box_add(obj);
   evas_object_size_hint_weight_set(wd->box, EVAS_HINT_EXPAND,
                                    EVAS_HINT_EXPAND);
   evas_object_size_hint_weight_set(content, EVAS_HINT_EXPAND,
                                    EVAS_HINT_EXPAND);
   evas_object_size_hint_fill_set(content, EVAS_HINT_FILL,
                                  EVAS_HINT_FILL);
   evas_object_show(content);
   evas_object_size_hint_min_get(content, &min_w, &min_h);
   evas_object_size_hint_min_set(wd->box, min_w, min_h);
   elm_box_pack_end(wd->box, content);

   evas_object_event_callback_add(wd->box, EVAS_CALLBACK_RESIZE,
                                  _content_resize, obj);
   evas_object_event_callback_add(wd->box, EVAS_CALLBACK_DEL,
                                  _content_del, obj);

   elm_widget_sub_object_add(obj, wd->box);
   edje_object_part_swallow(wd->base, "elm.swallow.content", wd->box);

   wd->content = content;
   wd->dir = ELM_CTXPOPUP_DIRECTION_UNKNOWN;

   if (wd->visible)
     _sizing_eval(obj);
}
