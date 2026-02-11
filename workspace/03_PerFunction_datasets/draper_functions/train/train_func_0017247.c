_calc_job_cb(void *data)
{
   Elm_Photocam_Smart_Data *sd = data;
   Evas_Coord minw, minh;

   minw = sd->size.w;
   minh = sd->size.h;
   if (sd->resized)
     {
        sd->resized = EINA_FALSE;
        if (sd->mode != ELM_PHOTOCAM_ZOOM_MODE_MANUAL)
          {
             double tz = sd->zoom;
             sd->zoom = 0.0;
             elm_photocam_zoom_set(ELM_WIDGET_DATA(sd)->obj, tz);
          }
     }
   if ((minw != sd->minw) || (minh != sd->minh))
     {
        sd->minw = minw;
        sd->minh = minh;

        evas_object_smart_callback_call(sd->pan_obj, "changed", NULL);
        _sizing_eval(ELM_WIDGET_DATA(sd)->obj);
     }
   sd->calc_job = NULL;
   evas_object_smart_changed(sd->pan_obj);
}
