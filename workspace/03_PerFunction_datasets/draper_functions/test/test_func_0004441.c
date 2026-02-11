_elm_spinner_smart_theme(Evas_Object *obj)
{
   Eina_Bool ret;
   ret = elm_layout_theme_set(obj, "spinner", "base",
                              elm_widget_style_get(obj));

   if (_elm_config->access_mode == ELM_ACCESS_MODE_ON)
     _access_spinner_register(obj);

   return ret;
}
