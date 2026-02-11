elm_widget_style_get(const Evas_Object *obj)
{
   API_ENTRY return NULL;
   if (sd->style) return sd->style;
   return "default";
}
