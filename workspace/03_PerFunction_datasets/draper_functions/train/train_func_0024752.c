champlain_viewport_set_adjustments (ChamplainViewport *viewport,
    ChamplainAdjustment *hadjustment,
    ChamplainAdjustment *vadjustment)
{
  ChamplainViewportPrivate *priv = CHAMPLAIN_VIEWPORT (viewport)->priv;

  if (hadjustment != priv->hadjustment)
    {
      if (priv->hadjustment)
        {
          g_signal_handlers_disconnect_by_func (priv->hadjustment,
              hadjustment_value_notify_cb,
              viewport);
          g_object_unref (priv->hadjustment);
        }

      if (hadjustment)
        {
          g_object_ref (hadjustment);
          g_signal_connect (hadjustment, "notify::value",
              G_CALLBACK (hadjustment_value_notify_cb),
              viewport);
        }

      priv->hadjustment = hadjustment;
    }

  if (vadjustment != priv->vadjustment)
    {
      if (priv->vadjustment)
        {
          g_signal_handlers_disconnect_by_func (priv->vadjustment,
              vadjustment_value_notify_cb,
              viewport);
          g_object_unref (priv->vadjustment);
        }

      if (vadjustment)
        {
          g_object_ref (vadjustment);
          g_signal_connect (vadjustment, "notify::value",
              G_CALLBACK (vadjustment_value_notify_cb),
              viewport);
        }

      priv->vadjustment = vadjustment;
    }
}
