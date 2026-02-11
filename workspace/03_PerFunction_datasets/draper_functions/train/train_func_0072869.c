champlain_adjustment_set_step_increment (ChamplainAdjustment *adjustment,
    gdouble step)
{
  ChamplainAdjustmentPrivate *priv = adjustment->priv;

  if (priv->step_increment != step)
    {
      priv->step_increment = step;

      g_signal_emit (adjustment, signals[CHANGED], 0);

      g_object_notify (G_OBJECT (adjustment), "step-increment");
    }
}
