tracker_controller_set_property (GObject      *object,
                                 guint         param_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
	TrackerControllerPrivate *priv = TRACKER_CONTROLLER (object)->priv;

	switch (param_id) {
	case PROP_SHUTDOWN_TIMEOUT:
		priv->shutdown_timeout = g_value_get_uint (value);
		break;
	case PROP_EXTRACTOR:
		priv->extractor = g_value_dup_object (value);
		break;
	}
}
