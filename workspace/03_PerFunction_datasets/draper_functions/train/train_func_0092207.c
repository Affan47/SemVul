_content_set_hook(Evas_Object *obj, const char *part,
                                 Evas_Object *content)
{
   ELM_CHECK_WIDTYPE(obj, widtype);
   char buff[3];
   unsigned int i;
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd) return;
   if (!part || !strcmp(part, "default"))
     _content_set(obj, content);
   else if (!strcmp(part, "title,icon"))
     _title_icon_set(obj, content);
   else if (!strncmp(part, "button", 6))
     {
        part += 6;
        for (i = 0; i < ELM_POPUP_ACTION_BUTTON_MAX; i++)
          {
             snprintf(buff, sizeof(buff), "%u", i+1);
             if (!strncmp(part, buff, sizeof(buff)))
               {
                  _action_button_set(obj, content, i+1);
                  break;
               }
          }
      }
   else
     WRN("The part name is invalid! : popup=%p", obj);
}
