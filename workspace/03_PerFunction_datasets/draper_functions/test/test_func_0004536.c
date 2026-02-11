_text_get_hook(const Evas_Object *obj, const char *part)
{
   ELM_CHECK_WIDTYPE(obj, widtype) NULL;
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return NULL;

   if (!part || !strcmp(part, "default"))
     {
        return wd->labeltxt;
     }
   else if (!strcmp(part, "guide"))
     {
        return wd->guidetexttxt;
     }
   return NULL;
}
