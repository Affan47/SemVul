clutter_timeline_get_step_progress (ClutterTimeline *timeline,
                                    gint            *n_steps,
                                    ClutterStepMode *step_mode)
{
  g_return_val_if_fail (CLUTTER_IS_TIMELINE (timeline), FALSE);

  if (timeline->priv->progress_mode != CLUTTER_STEPS ||
      timeline->priv->progress_mode != CLUTTER_STEP_START ||
      timeline->priv->progress_mode != CLUTTER_STEP_END)
    return FALSE;

  if (n_steps != NULL)
    *n_steps = timeline->priv->n_steps;

  if (step_mode != NULL)
    *step_mode = timeline->priv->step_mode;

  return TRUE;
}
