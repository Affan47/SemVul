_FILE_CHOSEN_fwd(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
   Widget_Data *wd = elm_widget_data_get(data);
   const char *file = event_info;
   char *s;

   s = elm_entry_utf8_to_markup(file);
   if (!s) return;
   elm_object_text_set(wd->entry, s);
   free(s);
   evas_object_smart_callback_call(data, SIG_FILE_CHOSEN, event_info);
}
