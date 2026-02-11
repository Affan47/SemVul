_smart_event_post_move(void *data, Evas *e __UNUSED__)
{
   Smart_Data *sd = data;

   if (sd->down.want_dragged)
     {
        int start = 0;

        if (sd->down.hold_parent)
          {
             if ((sd->down.dir_x) && !can_scroll(sd, sd->down.hdir))
               {
                  sd->down.dir_x = EINA_FALSE;
               }
             if ((sd->down.dir_y) && !can_scroll(sd, sd->down.vdir))
               {
                  sd->down.dir_y = EINA_FALSE;
               }
          }
        if (sd->down.dir_x)
          {
             if ((!sd->widget) ||
                 (!elm_widget_drag_child_locked_x_get(sd->widget)))
               {
                  sd->down.want_dragged = EINA_FALSE;
                  sd->down.dragged = EINA_TRUE;
                  if (sd->widget)
                    {
                       elm_widget_drag_lock_x_set(sd->widget, 1);
                    }
                  start = 1;
               }
             else
               sd->down.dir_x = EINA_FALSE;
          }
        if (sd->down.dir_y)
          {
             if ((!sd->widget) ||
                 (!elm_widget_drag_child_locked_y_get(sd->widget)))
               {
                  sd->down.want_dragged = EINA_FALSE;
                  sd->down.dragged = EINA_TRUE;
                  if (sd->widget)
                    {
                       elm_widget_drag_lock_y_set(sd->widget, 1);
                    }
                  start = 1;
               }
             else
               sd->down.dir_y = EINA_FALSE;
          }
        if ((!sd->down.dir_x) && (!sd->down.dir_y))
          {
             sd->down.cancelled = EINA_TRUE;
          }
        if (start) _smart_drag_start(sd->smart_obj);
     }
   return EINA_TRUE;
}
