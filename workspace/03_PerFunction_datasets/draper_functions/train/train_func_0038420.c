e_icon_file_edje_set(Evas_Object *obj, const char *file, const char *part)
{
   E_Smart_Data *sd;

   if (evas_object_smart_smart_get(obj) != _e_smart) SMARTERR(0);
   if (!(sd = evas_object_smart_data_get(obj)))
     return EINA_FALSE;


   if (sd->obj) evas_object_del(sd->obj);
   sd->loading = 0;
   if (sd->fdo)
     {
        eina_stringshare_del(sd->fdo);
        sd->fdo = NULL;
     }

   if (sd->timer) ecore_timer_del(sd->timer);
   sd->timer = NULL;
   if (sd->guessing_animation) ecore_timer_del(sd->guessing_animation);
   sd->guessing_animation = NULL;
   sd->frame = 0;
   sd->frame_count = 0;
   sd->edje = EINA_TRUE;

   sd->obj = edje_object_add(evas_object_evas_get(obj));
   edje_object_file_set(sd->obj, file, part);
   if (edje_object_load_error_get(sd->obj) != EDJE_LOAD_ERROR_NONE)
     return EINA_FALSE;
   if (evas_object_visible_get(obj)) evas_object_show(sd->obj);
   evas_object_smart_member_add(sd->obj, obj);
   _e_icon_smart_reconfigure(sd);
   return EINA_TRUE;
}
