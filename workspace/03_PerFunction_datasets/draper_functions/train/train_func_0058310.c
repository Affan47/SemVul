_font_overlay_change(void *data       __UNUSED__,
                     Evas_Object *obj __UNUSED__,
                     void *event_info __UNUSED__)
{
   Elm_Text_Class_Data *tc_data;
   Eina_List *l;

   EINA_LIST_FOREACH(fndata.text_classes, l, tc_data)
     {
        if (tc_data->font)
          {
             char *name;

             name = elm_font_fontconfig_name_get(tc_data->font,
                                                 tc_data->style);
             elm_config_font_overlay_set(tc_data->name, name,
                                         tc_data->size ? tc_data->size : -100);
             elm_font_fontconfig_name_free(name);
          }
        else
          elm_config_font_overlay_unset(tc_data->name);
     }

   elm_config_font_overlay_apply();
   elm_config_all_flush();
   elm_config_save();


}
