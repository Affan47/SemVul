elm_multibuttonentry_last_item_get(const Evas_Object *obj)
{
   ELM_CHECK_WIDTYPE(obj, widtype) NULL;
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return NULL;
   return eina_list_data_get(eina_list_last(wd->items));
}
