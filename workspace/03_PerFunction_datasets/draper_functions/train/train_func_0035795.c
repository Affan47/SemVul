_ecore_fb_li_device_event_syn(Ecore_Fb_Input_Device *dev, struct input_event *iev __UNUSED__)
{
   if (!dev->listen) return;

   if (dev->mouse.event == ECORE_EVENT_MOUSE_MOVE)
     {
        Ecore_Event_Mouse_Move *ev;
        ev = calloc(1,sizeof(Ecore_Event_Mouse_Move));
        ev->x = dev->mouse.x;
        ev->y = dev->mouse.y;
        ev->root.x = ev->x;
        ev->root.y = ev->y;
        ev->timestamp = ecore_loop_time_get() * 1000.0;
     }
   else if (dev->mouse.event == ECORE_EVENT_MOUSE_BUTTON_DOWN)
     {
        Ecore_Event_Mouse_Button *ev;
        ev = calloc(1, sizeof(Ecore_Event_Mouse_Button));
        ev->x = dev->mouse.x;
        ev->y = dev->mouse.y;
        ev->root.x = ev->x;
        ev->root.y = ev->y;
        ev->buttons = 1;
        ev->timestamp = ecore_loop_time_get() * 1000.0;
        ecore_event_add(ECORE_EVENT_MOUSE_BUTTON_DOWN, ev, NULL, NULL);
     }
   else if (dev->mouse.event == ECORE_EVENT_MOUSE_BUTTON_UP)
     {
        Ecore_Event_Mouse_Button *ev;
        ev = calloc(1, sizeof(Ecore_Event_Mouse_Button));
        ev->x = dev->mouse.x;
        ev->y = dev->mouse.y;
        ev->root.x = ev->x;
        ev->root.y = ev->y;
        ev->buttons = 1;
        ev->timestamp = ecore_loop_time_get() * 1000.0;
        ecore_event_add(ECORE_EVENT_MOUSE_BUTTON_UP, ev, NULL, NULL);
     }
}
