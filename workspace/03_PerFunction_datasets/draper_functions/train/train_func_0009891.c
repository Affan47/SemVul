_theme_hook(Evas_Object *obj)
{
   Widget_Data *wd = elm_widget_data_get(obj);
   const char *style = elm_widget_style_get(obj);
   char buf[1024];

   if (!wd) return;
   _elm_widget_mirrored_reload(obj);
   _mirrored_set(obj, elm_widget_mirrored_get(obj));

   _elm_theme_object_set(obj, wd->edje, "fileselector_entry", "base", style);
   if (elm_object_disabled_get(obj))
      edje_object_signal_emit(wd->edje, "elm,state,disabled", "elm");

   if (!style) style = "default";
   snprintf(buf, sizeof(buf), "fileselector_entry/%s", style);
   elm_widget_style_set(wd->button, buf);
   elm_widget_style_set(wd->entry, buf);

   edje_object_part_swallow(obj, "elm.swallow.button", wd->button);
   edje_object_part_swallow(obj, "elm.swallow.entry", wd->entry);

   edje_object_message_signal_process(wd->edje);
   edje_object_scale_set
     (wd->edje, elm_widget_scale_get(obj) * _elm_config->scale);
   _sizing_eval(obj);
}
