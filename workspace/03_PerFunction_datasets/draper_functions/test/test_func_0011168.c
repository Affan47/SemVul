elm_entry_cursor_is_format_get(const Evas_Object *obj)
{
   ELM_CHECK_WIDTYPE(obj, widtype) EINA_FALSE;
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return EINA_FALSE;
   return edje_object_part_text_cursor_is_format_get(wd->ent, "elm.text", EDJE_CURSOR_MAIN);
}
