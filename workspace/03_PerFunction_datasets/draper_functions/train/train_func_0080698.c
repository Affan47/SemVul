wnck_task_button_glow (WnckTask *task)
{
  GTimeVal tv;
  gdouble now;
  gfloat fade_opacity, loop_time;
  gint fade_max_loops;
  gboolean stopped;

  g_get_current_time (&tv);
  now = (tv.tv_sec * (1.0 * G_USEC_PER_SEC) +
        tv.tv_usec) / G_USEC_PER_SEC;

  if (task->glow_start_time <= G_MINDOUBLE)
    task->glow_start_time = now;

  gtk_widget_style_get (GTK_WIDGET (task->tasklist), "fade-opacity", &fade_opacity,
                                                     "fade-loop-time", &loop_time,
                                                     "fade-max-loops", &fade_max_loops,
                                                     NULL);

  if (task->button_glow == 0)
    {

      task->glow_factor = fade_opacity * 0.5;
      stopped = TRUE;
    }
  else
    {
      task->glow_factor = fade_opacity * (0.5 -
                                          0.5 * cos ((now - task->glow_start_time) *
                                                     M_PI * 2.0 / loop_time));

      if (now - task->start_needs_attention > loop_time * 1.0 * fade_max_loops)
        stopped = ABS (task->glow_factor - fade_opacity * 0.5) < 0.05;
      else
        stopped = FALSE;
    }

  gtk_widget_queue_draw (task->button);

  if (stopped)
    wnck_task_stop_glow (task);

  return !stopped;
}
