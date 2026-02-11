external_photocam_param_set(void *data __UNUSED__, Evas_Object *obj, const Edje_External_Param *param)
{
   if (!strcmp(param->name, "file"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
	  {
	     elm_photocam_file_set(obj, param->s);
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "zoom"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_DOUBLE)
	  {
	     elm_photocam_zoom_set(obj, param->d);
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "zoom mode"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
	  {
	     Elm_Photocam_Zoom_Mode set = _zoom_mode_setting_get(param->s);
	     if (set == ELM_PHOTOCAM_ZOOM_MODE_LAST) return EINA_FALSE;
	     elm_photocam_zoom_mode_set(obj, set);
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "paused"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
	  {
	     elm_photocam_paused_set(obj, param->i);
	     return EINA_TRUE;
	  }
     }

   ERR("unknown parameter '%s' of type '%s'",
       param->name, edje_external_param_type_str(param->type));

   return EINA_FALSE;
}
