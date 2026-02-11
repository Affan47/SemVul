champlain_adjustment_set_values (ChamplainAdjustment *adjustment,
    gdouble value,
    gdouble lower,
    gdouble upper,
    gdouble step_increment)
{
  ChamplainAdjustmentPrivate *priv;
  gboolean emit_changed = FALSE;

  g_return_if_fail (CHAMPLAIN_IS_ADJUSTMENT (adjustment));

  priv = adjustment->priv;

  stop_interpolation (adjustment);

  g_object_freeze_notify (G_OBJECT (adjustment));

  if (priv->lower != lower)
    {
      priv->lower = lower;
      emit_changed = TRUE;

      g_object_notify (G_OBJECT (adjustment), "lower");
    }

  if (priv->upper != upper)
    {
      priv->upper = upper;
      emit_changed = TRUE;

      g_object_notify (G_OBJECT (adjustment), "upper");
    }

  if (priv->step_increment != step_increment)
    {
      priv->step_increment = step_increment;
      emit_changed = TRUE;

      g_object_notify (G_OBJECT (adjustment), "step-increment");
    }

  champlain_adjustment_set_value (adjustment, value);

  if (emit_changed)
    g_signal_emit (G_OBJECT (adjustment), signals[CHANGED], 0);

  g_object_thaw_notify (G_OBJECT (adjustment));
}
