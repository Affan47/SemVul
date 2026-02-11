_event_process(void *data,
               Evas_Object *obj __UNUSED__,
               void *event_info,
               Evas_Callback_Type event_type)
{
   Pointer_Event _pe;
   Pointer_Event *pe = NULL;

   ELM_GESTURE_LAYER_DATA_GET(data, sd);


   if (_pointer_event_make(data, event_info, event_type, &_pe))
     pe = &_pe;


   {

      Gesture_Info **gitr = sd->gesture + 1;
      Tests_Array_Funcs *fitr = _glayer_tests_array + 1;
      for (; fitr->test; fitr++, gitr++)
        {
           if (IS_TESTED_GESTURE(*gitr))
             fitr->test(data, pe, event_info, event_type, (*gitr)->g_type);
        }
   }

   if (_event_flag_get(event_info, event_type) & EVAS_EVENT_FLAG_ON_HOLD)
     _event_history_add(data, event_info, event_type);


   if ((event_type == EVAS_CALLBACK_MOUSE_DOWN) ||
       (event_type == EVAS_CALLBACK_MULTI_DOWN) ||
       (event_type == EVAS_CALLBACK_MOUSE_MOVE) ||
       (event_type == EVAS_CALLBACK_MULTI_MOVE))
     {
        sd->touched = _touched_device_add(sd->touched, pe);
     }
   else if ((event_type == EVAS_CALLBACK_MOUSE_UP) ||
            (event_type == EVAS_CALLBACK_MULTI_UP))
     {
        sd->touched = _touched_device_remove(sd->touched, pe);
     }


   Eina_Bool states_reset = _clear_if_finished(data);
   if (sd->glayer_continues_enable)
     _continues_gestures_restart(data, states_reset);
}
