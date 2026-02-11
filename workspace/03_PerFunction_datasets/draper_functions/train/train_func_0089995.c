nm_ap_set_address (NMAccessPoint *ap, const struct ether_addr * addr)
{
	NMAccessPointPrivate *priv;

	g_return_if_fail (NM_IS_AP (ap));
	g_return_if_fail (addr != NULL);

	priv = NM_AP_GET_PRIVATE (ap);

	if (memcmp (addr, &priv->address, sizeof (priv->address))) {
		memcpy (&NM_AP_GET_PRIVATE (ap)->address, addr, sizeof (struct ether_addr));
		g_object_notify (G_OBJECT (ap), NM_AP_HW_ADDRESS);
	}
}
