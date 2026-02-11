_entry_focus_out_cb(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Widget_Data *wd = elm_widget_data_get(data);
   const char *str;

   if (!wd) return;

   str = elm_object_text_get(wd->entry);
   if (strlen(str))
     _add_button_item(data, str, MULTIBUTTONENTRY_POS_END, NULL, NULL, NULL);
}
