deactivate (NMModem *_self, NMDevice *device)
{
	NMModemBroadband *self = NM_MODEM_BROADBAND (_self);


	g_clear_object (&self->priv->ipv4_config);
	g_clear_object (&self->priv->ipv6_config);
	g_clear_object (&self->priv->bearer);

	self->priv->pin_tries = 0;


	NM_MODEM_CLASS (nm_modem_broadband_parent_class)->deactivate (_self, device);
}
