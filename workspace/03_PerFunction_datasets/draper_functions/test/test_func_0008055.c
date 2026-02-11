network_provider_set_property (GObject       *object,
                               guint          prop_id,
                               const GValue  *value,
                               GParamSpec    *pspec)
{
	TrackerNetworkProviderDummyPrivate *priv;

	priv = TRACKER_NETWORK_PROVIDER_DUMMY_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_NAME:
		g_free (priv->name);
		priv->name = g_value_dup_string (value);
		g_object_notify (object, "name");
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	};
}
