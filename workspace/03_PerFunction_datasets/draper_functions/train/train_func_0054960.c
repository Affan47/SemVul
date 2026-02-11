_text_get_hook(const Evas_Object *obj, const char *part)
{
   ELM_CHECK_WIDTYPE(obj, widtype) NULL;
   const char *str = NULL;
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd) return NULL;
   if (!part || !strcmp(part, "default"))
     str = _content_text_get(obj);
   else if (!strcmp(part, "title,text"))
     str = _title_text_get(obj);
   else
     WRN("The part name is invalid! : popup=%p", obj);
   return str;
}
