_ecore_fb_li_device_event_abs(Ecore_Fb_Input_Device *dev, struct input_event *iev)
{
   static int prev_pressure = 0;
   int pressure;

   if (!dev->listen) return;
   switch (iev->code)
     {
     case ABS_X:
        if (dev->mouse.w != 0)
          {
             int tmp;

             tmp = (int)((double)(iev->value - dev->mouse.min_w) / dev->mouse.rel_w);
             if (tmp < 0) dev->mouse.x = 0;
             else if (tmp > dev->mouse.w) dev->mouse.x = dev->mouse.w;
             else dev->mouse.x = tmp;
             dev->mouse.event = ECORE_EVENT_MOUSE_MOVE;
          }
        break;

     case ABS_Y:
        if (dev->mouse.h != 0)
          {
             int tmp;

             tmp = (int)((double)(iev->value - dev->mouse.min_h) / dev->mouse.rel_h);
             if (tmp < 0) dev->mouse.y = 0;
             else if (tmp > dev->mouse.h) dev->mouse.y = dev->mouse.h;
             else dev->mouse.y = tmp;
             dev->mouse.event = ECORE_EVENT_MOUSE_MOVE;
          }
        break;

     case ABS_PRESSURE:
        pressure = iev->value;
        if ((pressure) && (!prev_pressure))
          {

             dev->mouse.event = ECORE_EVENT_MOUSE_BUTTON_DOWN;
          }
        else if ((!pressure) && (prev_pressure))
          {

             dev->mouse.event = ECORE_EVENT_MOUSE_BUTTON_UP;
          }
        prev_pressure = pressure;
        break;
     }
}
