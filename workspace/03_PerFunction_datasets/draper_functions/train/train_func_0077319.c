glade_signal_model_get_property (GObject *object,
                                 guint prop_id,
                                 GValue *value,
                                 GParamSpec *pspec)
{
  GladeSignalModel *sig_model;

  g_return_if_fail (GLADE_IS_SIGNAL_MODEL (object));

  sig_model = GLADE_SIGNAL_MODEL (object);

  switch (prop_id)
    {
      case PROP_WIDGET:
        g_value_set_object (value, sig_model->priv->widget);
      break;
      case PROP_SIGNALS:
        g_value_set_pointer (value, sig_model->priv->signals);
      break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
