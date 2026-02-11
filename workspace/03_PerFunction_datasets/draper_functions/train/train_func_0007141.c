_g_layer_zoom_start_cb(void *data,
                       void *event_info)
{
   Elm_Gesture_Zoom_Info *p = event_info;
   Elm_Photocam_Smart_Data *sd = data;
   double marginx = 0, marginy = 0;
   Evas_Coord rw, rh;
   int x, y, w, h;

   if (sd->g_layer_zoom.bounce.animator)
     {
        ecore_animator_del(sd->g_layer_zoom.bounce.animator);
        sd->g_layer_zoom.bounce.animator = NULL;
     }
   sd->zoom_g_layer = EINA_TRUE;

   sd->s_iface->freeze_set(ELM_WIDGET_DATA(sd)->obj, EINA_TRUE);

   elm_photocam_image_region_get(ELM_WIDGET_DATA(sd)->obj, &x, &y, &w, &h);
   sd->s_iface->content_viewport_size_get(ELM_WIDGET_DATA(sd)->obj, &rw, &rh);

   if (rw > sd->size.nw)
     marginx = (rw - sd->size.nw) / 2;
   if (rh > sd->size.nh)
     marginy = (rh - sd->size.nh) / 2;

   sd->g_layer_start = sd->zoom;

   sd->zoom_point_x = x + ((p->x - marginx) * sd->zoom) +
     sd->g_layer_zoom.imx;
   sd->zoom_point_y = y + ((p->y - marginy) * sd->zoom) +
     sd->g_layer_zoom.imy;

   return EVAS_EVENT_FLAG_NONE;
}
