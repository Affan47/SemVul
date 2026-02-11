elm_gesture_layer_hold_events_get(const Evas_Object *obj)
{
   ELM_GESTURE_LAYER_CHECK(obj) EINA_FALSE;
   ELM_GESTURE_LAYER_DATA_GET(obj, sd);

   return !sd->repeat_events;
}
