set_property (GObject *object,
              guint prop_id,
			  const GValue *value,
              GParamSpec *pspec)
{
	NMModemBroadband *self = NM_MODEM_BROADBAND (object);

	switch (prop_id) {
	case PROP_MODEM:

		self->priv->modem_object = g_value_dup_object (value);
		self->priv->modem_iface = mm_object_get_modem (self->priv->modem_object);
		g_assert (self->priv->modem_iface != NULL);
		g_signal_connect (self->priv->modem_iface,
                          "state-changed",
                          G_CALLBACK (modem_state_changed),
                          self);

		g_object_set (object,
		              NM_MODEM_ENABLED, (mm_modem_get_state (self->priv->modem_iface) >= MM_MODEM_STATE_ENABLED),
		              NM_MODEM_CONNECTED, (mm_modem_get_state (self->priv->modem_iface) >= MM_MODEM_STATE_CONNECTED),
		              NULL);


		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
