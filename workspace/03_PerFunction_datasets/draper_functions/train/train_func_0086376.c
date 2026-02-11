elm_entry_input_panel_enabled_set(Evas_Object *obj, Eina_Bool enabled)
{
   ELM_CHECK_WIDTYPE(obj, widtype);
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return;

   wd->input_panel_enable = enabled;
   edje_object_part_text_input_panel_enabled_set(wd->ent, "elm.text", enabled);
}
