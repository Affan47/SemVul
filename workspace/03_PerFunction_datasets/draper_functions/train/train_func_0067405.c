_zoom_anim_cb(void *data)
{
   double t;
   Eina_Bool go;
   Evas_Object *obj = data;

   ELM_PHOTOCAM_DATA_GET(obj, sd);

   t = ecore_loop_time_get();
   if (t >= sd->t_end)
     t = 1.0;
   else if (sd->t_end > sd->t_start)
     t = (t - sd->t_start) / (sd->t_end - sd->t_start);
   else
     t = 1.0;
   t = 1.0 - t;
   t = 1.0 - (t * t);
   go = _zoom_do(obj, t);
   if (!go)
     {
        sd->no_smooth--;
        if (!sd->no_smooth) _smooth_update(data);
        sd->zoom_animator = NULL;
        evas_object_smart_callback_call(obj, SIG_ZOOM_STOP, NULL);
     }

   return go;
}
