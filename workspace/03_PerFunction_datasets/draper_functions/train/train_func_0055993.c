get_shadow_slope_width (ChamplainLabel *label)
{
  ChamplainLabelPrivate *priv = label->priv;
  gint x;

  if (priv->alignment == PANGO_ALIGN_LEFT)
    x = -40 * SLOPE;
  else
    x = -58 * SLOPE;

  return x;
}
