clutter_stage_cogl_schedule_update (ClutterStageWindow *stage_window,
                                    gint                sync_delay)
{
  ClutterStageCogl *stage_cogl = CLUTTER_STAGE_COGL (stage_window);
  gint64 now;
  float refresh_rate;
  gint64 refresh_interval;

  if (stage_cogl->update_time != -1)
    return;

  now = g_get_monotonic_time ();

  if (sync_delay < 0)
    {
      stage_cogl->update_time = now;
      return;
    }


  if (stage_cogl->last_presentation_time == 0||
      stage_cogl->last_presentation_time < now - 150000)
    {
      stage_cogl->update_time = now;
      return;
    }

  refresh_rate = stage_cogl->refresh_rate;
  if (refresh_rate == 0.0)
    refresh_rate = 60.0;

  refresh_interval = (gint64) (0.5 + 1000000 / refresh_rate);
  if (refresh_interval == 0)
    refresh_interval = 16667;

  stage_cogl->update_time = stage_cogl->last_presentation_time + 1000 * sync_delay;

  while (stage_cogl->update_time < now)
    stage_cogl->update_time += refresh_interval;
}
