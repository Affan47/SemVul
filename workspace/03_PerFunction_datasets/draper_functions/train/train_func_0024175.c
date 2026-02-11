elm_widget_scale_set(Evas_Object *obj,
                     double       scale)
{
   API_ENTRY return;
   if (scale <= 0.0) scale = 0.0;
   if (sd->scale != scale)
     {
        sd->scale = scale;
        elm_widget_theme(obj);
     }
}
