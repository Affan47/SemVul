mx_adjustment_set_values (MxAdjustment *adjustment,
                          gdouble       value,
                          gdouble       lower,
                          gdouble       upper,
                          gdouble       step_increment,
                          gdouble       page_increment,
                          gdouble       page_size)
{
  MxAdjustmentPrivate *priv;
  gboolean emit_changed = FALSE;

  g_return_if_fail (MX_IS_ADJUSTMENT (adjustment));
  g_return_if_fail (page_size >= 0 && page_size <= G_MAXDOUBLE);
  g_return_if_fail (step_increment >= 0 && step_increment <= G_MAXDOUBLE);
  g_return_if_fail (page_increment >= 0 && page_increment <= G_MAXDOUBLE);

  priv = adjustment->priv;

  emit_changed = FALSE;

  g_object_freeze_notify (G_OBJECT (adjustment));

  emit_changed |= _mx_adjustment_set_lower (adjustment, lower);
  emit_changed |= _mx_adjustment_set_upper (adjustment, upper);
  emit_changed |= _mx_adjustment_set_step_increment (adjustment,
                                                     step_increment);
  emit_changed |= _mx_adjustment_set_page_increment (adjustment,
                                                     page_increment);
  emit_changed |= _mx_adjustment_set_page_size (adjustment, page_size);

  if (value != priv->value)
    {
      mx_adjustment_set_value (adjustment, value);
      emit_changed = TRUE;
    }

  if (emit_changed)
    mx_adjustment_emit_changed (adjustment);

  g_object_thaw_notify (G_OBJECT (adjustment));
}
