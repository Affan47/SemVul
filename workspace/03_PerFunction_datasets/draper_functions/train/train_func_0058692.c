_content_get_hook(const Evas_Object *obj, const char *part)
{
   ELM_CHECK_WIDTYPE(obj, widtype) NULL;
   Widget_Data *wd;
   if ((part) && (strcmp(part, "default"))) return NULL;
   wd = elm_widget_data_get(obj);
   if (!wd) return NULL;
   return wd->content;
}
