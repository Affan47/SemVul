clutter_stage_gdk_set_user_resizable (ClutterStageWindow *stage_window,
                                      gboolean            is_resizable)
{
  ClutterStageGdk *stage_gdk = CLUTTER_STAGE_GDK (stage_window);
  GdkWMFunction function;

  if (stage_gdk->window == NULL)
    return;

  function = GDK_FUNC_MOVE | GDK_FUNC_MINIMIZE | GDK_FUNC_CLOSE;
  if (is_resizable)
    function |= GDK_FUNC_RESIZE | GDK_FUNC_MAXIMIZE;

  gdk_window_set_functions (stage_gdk->window, function);

  clutter_stage_gdk_set_gdk_geometry (stage_gdk);
}
