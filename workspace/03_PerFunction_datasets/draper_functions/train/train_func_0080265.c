elm_photocam_gesture_enabled_set(Evas_Object *obj,
                                 Eina_Bool gesture)
{
   ELM_PHOTOCAM_CHECK(obj);
   ELM_PHOTOCAM_DATA_GET(obj, sd);

   gesture = !!gesture;

   if (sd->do_gesture == gesture) return;

   sd->do_gesture = gesture;

   if (sd->g_layer)
     {
        evas_object_del(sd->g_layer);
        sd->g_layer = NULL;
     }

   if (!gesture) return;

   sd->g_layer = elm_gesture_layer_add(obj);
   if (!sd->g_layer) return;

   elm_gesture_layer_attach(sd->g_layer, obj);
   elm_gesture_layer_cb_set
     (sd->g_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_START,
     _g_layer_zoom_start_cb, sd);
   elm_gesture_layer_cb_set
     (sd->g_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_MOVE,
     _g_layer_zoom_move_cb, sd);
   elm_gesture_layer_cb_set
     (sd->g_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_END,
     _g_layer_zoom_end_cb, sd);
   elm_gesture_layer_cb_set
     (sd->g_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_ABORT,
     _g_layer_zoom_end_cb, sd);
}
