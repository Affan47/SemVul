_mouse_down(void *data, Evas *evas __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Widget_Data *wd = elm_widget_data_get(data);
   Evas_Event_Mouse_Down *ev = event_info;
   if (!wd) return;
   if (wd->disabled) return;
   if (ev->event_flags & EVAS_EVENT_FLAG_ON_HOLD) return;
   wd->downx = ev->canvas.x;
   wd->downy = ev->canvas.y;
   if (ev->button == 1)
     {
        if (wd->longpress_timer) ecore_timer_del(wd->longpress_timer);
        wd->longpress_timer = ecore_timer_add(_elm_config->longpress_timeout, _long_press, data);
     }
   else if (ev->button == 3)
     {
        if (_elm_config->desktop_entry)
          _menu_press(data);
     }
}
