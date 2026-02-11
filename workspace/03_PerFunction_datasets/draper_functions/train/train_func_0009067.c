mx_viewport_set_property (GObject      *object,
                          guint         prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  MxViewport *viewport = MX_VIEWPORT (object);
  MxViewportPrivate *priv = viewport->priv;

  switch (prop_id)
    {
    case PROP_X_ORIGIN:
      mx_viewport_set_origin (viewport,
                              g_value_get_float (value),
                              priv->y,
                              priv->z);
      break;

    case PROP_Y_ORIGIN:
      mx_viewport_set_origin (viewport,
                              priv->x,
                              g_value_get_float (value),
                              priv->z);
      break;

    case PROP_Z_ORIGIN:
      mx_viewport_set_origin (viewport,
                              priv->x,
                              priv->y,
                              g_value_get_float (value));
      break;

    case PROP_HADJUST:
      scrollable_set_adjustments (MX_SCROLLABLE (object),
                                  g_value_get_object (value),
                                  priv->vadjustment);
      break;

    case PROP_VADJUST:
      scrollable_set_adjustments (MX_SCROLLABLE (object),
                                  priv->hadjustment,
                                  g_value_get_object (value));
      break;

    case PROP_SYNC_ADJUST:
      mx_viewport_set_sync_adjustments (viewport, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
