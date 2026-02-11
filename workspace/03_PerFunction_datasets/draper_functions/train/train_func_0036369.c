elm_map_paused_set(Evas_Object *obj,
                   Eina_Bool paused)
{
#ifdef HAVE_ELEMENTARY_ECORE_CON
   ELM_MAP_CHECK(obj);
   ELM_MAP_DATA_GET(obj, sd);

   if (sd->paused == !!paused) return;
   sd->paused = !!paused;
   if (sd->paused)
     {
        if (sd->zoom_animator)
          {
             if (sd->zoom_animator) ecore_animator_del(sd->zoom_animator);
             sd->zoom_animator = NULL;
             _zoom_do(sd, sd->zoom);
          }
        edje_object_signal_emit(ELM_WIDGET_DATA(sd)->resize_obj,
                                "elm,state,busy,stop", "elm");
     }
   else
     {
        if (sd->download_num >= 1)
          edje_object_signal_emit(ELM_WIDGET_DATA(sd)->resize_obj,
                                  "elm,state,busy,start", "elm");
     }
#else
   (void)obj;
   (void)paused;
#endif
}
