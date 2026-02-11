update_water()
{
  gboolean status = TRUE;
  double y1 = 0;
  gint min = BASE_LINE - LEFT_CANAL_HEIGHT;


  if(animation)
    return;
  animation = TRUE;

  if((!canallock_left_up && !lock_water_low) ||
     (!canallock_right_up && lock_water_low))
    {
      status = !lock_water_low;
      lock_water_low = !lock_water_low;
      y1 = BASE_LINE - RIGHT_CANAL_HEIGHT;
    }
  else
    {

      animation = FALSE;
      return;
    }

  timer_item = canal_middle_item;
  timer_item_limit_y = (status ? min :
			y1);
  timer_step_y1 = (status ? 2 : -2);
  timer_step_x1 = 0;

  gc_item_focus_remove(tuxboat_item, NULL);

  timer_id = g_timeout_add (ANIMATE_SPEED, animate_step, NULL);
}
