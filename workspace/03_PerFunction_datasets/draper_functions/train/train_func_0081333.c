show_controls (VideoApp *app, gboolean vis)
{
  if (app->control == NULL)
    return;

  if (vis == TRUE && app->controls_showing == TRUE)
    {
      if (app->controls_timeout == 0)
        {
          app->controls_timeout =
            g_timeout_add_seconds (5, controls_timeout_cb, app);
        }

      return;
    }

  if (vis == TRUE && app->controls_showing == FALSE)
    {
      app->controls_showing = TRUE;

      clutter_stage_show_cursor (CLUTTER_STAGE (app->stage));
      clutter_actor_animate (app->control, CLUTTER_EASE_OUT_QUINT, 250,
                             "opacity", 224,
                             NULL);

      return;
    }

  if (vis == FALSE && app->controls_showing == TRUE)
    {
      app->controls_showing = FALSE;

      clutter_stage_hide_cursor (CLUTTER_STAGE (app->stage));
      clutter_actor_animate (app->control, CLUTTER_EASE_OUT_QUINT, 250,
                             "opacity", 0,
                             NULL);
      return;
    }
}
