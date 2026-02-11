elm_multibuttonentry_expanded_get(const Evas_Object *obj)
{
   ELM_CHECK_WIDTYPE(obj, widtype) -1;
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd) return -1;
     return (wd->view_state == MULTIBUTTONENTRY_VIEW_SHRINK ? EINA_FALSE : EINA_TRUE);
}
