compute_lines (ClutterFlowLayout *self,
               gfloat             avail_width,
               gfloat             avail_height)
{
  ClutterFlowLayoutPrivate *priv = self->priv;

  if (priv->orientation == CLUTTER_FLOW_HORIZONTAL)
    return get_columns (self, avail_width);
  else
    return get_rows (self, avail_height);
}
