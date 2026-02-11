external_frame_param_set(void *data __UNUSED__, Evas_Object *obj, const Edje_External_Param *param)
{
   if (!strcmp(param->name, "label"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
          {
             elm_object_text_set(obj, param->s);
             return EINA_TRUE;
          }
     }
   else if (!strcmp(param->name, "content"))
     {
        if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
          {
             Evas_Object *content =
                external_common_param_edje_object_get(obj,param);
             if ((strcmp(param->s, "")) && (!content)) return EINA_FALSE;
             elm_object_content_set(obj, content);
             return EINA_TRUE;
          }
     }

   ERR("unknown parameter '%s' of type '%s'",
       param->name, edje_external_param_type_str(param->type));

   return EINA_FALSE;
}
