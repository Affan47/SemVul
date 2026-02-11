elm_fileselector_entry_window_title_set(Evas_Object *obj, const char *title)
{
   ELM_CHECK_WIDTYPE(obj, widtype);
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return;
   elm_fileselector_button_window_title_set(wd->button, title);
}
