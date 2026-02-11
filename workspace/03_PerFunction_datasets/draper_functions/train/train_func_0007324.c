_state_report(Gesture_Info *gesture,
              void *info)
{

   if ((gesture->state != ELM_GESTURE_STATE_UNDEFINED) &&
       (gesture->fn[gesture->state].cb))


     {
        return gesture->fn[gesture->state].cb(
                 gesture->fn[gesture->state].user_data, info);
     }

   return EVAS_EVENT_FLAG_NONE;
}
