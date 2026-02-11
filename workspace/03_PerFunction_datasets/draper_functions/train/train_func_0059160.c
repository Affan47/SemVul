clutter_x11_get_stage_window (ClutterStage *stage)
{
  ClutterStageWindow *impl;

  g_return_val_if_fail (CLUTTER_IS_STAGE (stage), None);

  impl = _clutter_stage_get_window (stage);
  g_assert (CLUTTER_IS_STAGE_X11 (impl));

  return CLUTTER_STAGE_X11 (impl)->xwin;
}
