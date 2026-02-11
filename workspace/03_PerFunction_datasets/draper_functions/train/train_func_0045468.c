clutter_stage_gdk_set_fullscreen (ClutterStageWindow *stage_window,
                                  gboolean            is_fullscreen)
{
  ClutterStageGdk *stage_gdk = CLUTTER_STAGE_GDK (stage_window);
  ClutterStage *stage = CLUTTER_STAGE_COGL (stage_window)->wrapper;

  if (stage == NULL || CLUTTER_ACTOR_IN_DESTRUCTION (stage))
    return;

  if (stage_gdk->window == NULL)
    return;

  CLUTTER_NOTE (BACKEND, "%ssetting fullscreen", is_fullscreen ? "" : "un");

  if (is_fullscreen)
    gdk_window_fullscreen (stage_gdk->window);
  else
    gdk_window_unfullscreen (stage_gdk->window);
}
