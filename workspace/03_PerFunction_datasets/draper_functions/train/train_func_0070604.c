mx_gtk_light_switch_configure (GtkWidget         *lightswitch,
                               GdkEventConfigure *event)
{
  MxGtkLightSwitchPrivate *priv = MX_GTK_LIGHT_SWITCH_GET_PRIVATE (lightswitch);

  if (priv->active)
    priv->x = priv->trough_width - priv->switch_width;
  else
    priv->x = 0;

  return FALSE;
}
