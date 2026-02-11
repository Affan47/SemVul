animate_items(gpointer data)
{
  if(board_paused)
    return(FALSE);

  if(!animate_item)
    return(FALSE);


  animate_item_x = animate_item_x + wind_speed * sin(ang);
  animate_item_y = animate_item_y - wind_speed * cos(ang);

  g_object_set (animate_item,
		"center-x", (double)animate_item_x,
		"center-y", (double)animate_item_y,
		"radius-x", (double)animate_item_size,
		"radius-y", (double)animate_item_size,
		NULL);

  if(animate_item_size>MIN_DART_SIZE)
    animate_item_size--;

  if(--animate_item_distance == 0)
    {
      gc_sound_play_ogg ("sounds/brick.wav", NULL);


      guint points = add_points(animate_item_x, animate_item_y);


      g_signal_connect(animate_item,
		       "enter_notify_event", (GCallback) tooltip_event,
		       GINT_TO_POINTER(points));
      g_signal_connect(animate_item,
		       "leave_notify_event", (GCallback) tooltip_event,
		       GINT_TO_POINTER(-1));

      g_source_remove (animate_id);
      animate_id = 0;
      animate_item = NULL;


      display_windspeed();
    }
  return(TRUE);
}
