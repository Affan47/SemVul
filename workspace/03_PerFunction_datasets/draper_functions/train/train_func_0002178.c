gst_lfo_control_source_reset (GstLFOControlSource * self)
{
  GstControlSource *csource = GST_CONTROL_SOURCE (self);

  csource->get_value = NULL;
  csource->get_value_array = NULL;

  self->priv->type = self->priv->base = G_TYPE_INVALID;

  if (G_IS_VALUE (&self->priv->minimum_value))
    g_value_unset (&self->priv->minimum_value);
  if (G_IS_VALUE (&self->priv->maximum_value))
    g_value_unset (&self->priv->maximum_value);

  if (G_IS_VALUE (&self->priv->amplitude))
    g_value_unset (&self->priv->amplitude);
  if (G_IS_VALUE (&self->priv->offset))
    g_value_unset (&self->priv->offset);
}
