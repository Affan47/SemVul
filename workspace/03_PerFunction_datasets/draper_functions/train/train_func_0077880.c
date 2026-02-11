external_fileselector_entry_param_set(void *data __UNUSED__, Evas_Object *obj, const Edje_External_Param *param)
{
   if (!strcmp(param->name, "label"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
          {
             elm_object_text_set(obj, param->s);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "icon"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
          {
             Evas_Object *icon = external_common_param_icon_get(obj, param);
             if ((strcmp(param->s, "")) && (!icon)) return EINA_FALSE;
             elm_object_part_content_set(obj, "button icon", icon);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "path"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
          {
             elm_fileselector_entry_selected_set(obj, param->s);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "save"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
          {
             elm_fileselector_entry_is_save_set(obj, param->i);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "folder only"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
          {
             elm_fileselector_entry_folder_only_set(obj, param->i);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "expandable"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
          {
             elm_fileselector_entry_expandable_set(obj, param->i);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "inwin mode"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
          {
             elm_fileselector_entry_inwin_mode_set(obj, param->i);
             return EINA_TRUE;
          }
     }

   ERR("unknown parameter '%s' of type '%s'",
       param->name, edje_external_param_type_str(param->type));

   return EINA_FALSE;
}
