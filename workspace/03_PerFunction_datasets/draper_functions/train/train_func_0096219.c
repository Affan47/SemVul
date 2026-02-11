mx_gtk_light_switch_set_active (MxGtkLightSwitch *lightswitch,
                                gboolean          active)
{
  MxGtkLightSwitchPrivate *priv = MX_GTK_LIGHT_SWITCH_GET_PRIVATE (lightswitch);

  if (priv->active == active)
    {
      return;
    }
  else
    {
      priv->active = active;
      if (active == TRUE)
        {
          priv->x = priv->trough_width - priv->switch_width;
        }
      else
        {
          priv->x = 0;
        }

      gtk_widget_queue_draw ((GtkWidget *) lightswitch);

      g_object_notify (G_OBJECT (lightswitch), "active");
      g_signal_emit (lightswitch,
                     mx_gtk_light_switch_signals[SWITCH_FLIPPED],
                     0,
                     priv->active);
    }
}
