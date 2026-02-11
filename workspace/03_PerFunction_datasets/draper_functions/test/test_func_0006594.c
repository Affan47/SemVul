move_boat()
{


  if(animation)
    return;
  animation = TRUE;

  if(boat_position == BOAT_POS_LEFT && !lock_left_up)
    {
      boat_position = BOAT_POS_MIDDLE;
      timer_item_limit_x = LEFT_CANAL_WIDTH + (MIDDLE_CANAL_WIDTH - tuxboat_width)/2;
      timer_step_x1 = 2;
      g_object_set (tuxboat_item,
		    "svg-id", "#BOAT", NULL);
    }
  else if(boat_position == BOAT_POS_MIDDLE && !lock_left_up)
    {
      boat_position = BOAT_POS_LEFT;
      timer_item_limit_x = (LEFT_CANAL_WIDTH - tuxboat_width)/2;
      timer_step_x1 = -2;
      if (from == 1)
        {
          gamewon = TRUE;
          from = 0;
        }
      g_object_set (tuxboat_item,
		    "svg-id", "#BOAT", NULL);
    }
  else if(boat_position == BOAT_POS_MIDDLE && !lock_right_up)
    {
      boat_position = BOAT_POS_RIGHT;
      timer_item_limit_x = LEFT_CANAL_WIDTH + MIDDLE_CANAL_WIDTH + (RIGHT_CANAL_WIDTH - tuxboat_width)/2;
      timer_step_x1 = 2;
      if (from == 0)
        {
          gamewon = TRUE;
          from = 1;
        }
      g_object_set (tuxboat_item,
		    "svg-id", "#BOAT", NULL);
    }
  else if(boat_position == BOAT_POS_RIGHT && !lock_right_up)
    {
      boat_position = BOAT_POS_MIDDLE;
      timer_item_limit_x = LEFT_CANAL_WIDTH + (MIDDLE_CANAL_WIDTH - tuxboat_width)/2;
      timer_step_x1 = -2;
      g_object_set (tuxboat_item,
		    "svg-id", "#BOAT", NULL);
    }
  else
    {

      gc_sound_play_ogg ("sounds/crash.ogg", NULL);
      animation = FALSE;
      return;
    }

  gc_item_focus_remove(tuxboat_item, NULL);

  gc_sound_play_ogg ("sounds/eraser2.wav", NULL);

  timer_item = tuxboat_item;
  timer_step_y1 = 0;

  timer_id = g_timeout_add (ANIMATE_SPEED, animate_step, NULL);
}
