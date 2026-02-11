_e_smart_event_mouse_down(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Evas_Event_Mouse_Down *ev;
   E_Smart_Data *sd;

   sd = data;
   ev = event_info;
   if ((e_config->thumbscroll_enable) || (sd->thumbscroll.forced))
     {
        if (sd->down.momentum_animator)
          {
             ecore_animator_del(sd->down.momentum_animator);
             sd->down.momentum_animator = NULL;
          }
        if (ev->button == 1)
          {
             sd->down.now = 1;
             sd->down.dragged = 0;
             sd->down.dir_x = 0;
             sd->down.dir_y = 0;
             sd->down.x = ev->canvas.x;
             sd->down.y = ev->canvas.y;
             e_scrollframe_child_pos_get(sd->smart_obj,
                                         &sd->down.sx, &sd->down.sy);
             sd->down.locked = 0;
             memset(&(sd->down.history[0]), 0, sizeof(sd->down.history[0]) * 20);
             sd->down.history[0].timestamp = ecore_loop_time_get();
             sd->down.history[0].x = ev->canvas.x;
             sd->down.history[0].y = ev->canvas.y;
          }
     }
}
