gkm_xdg_trust_real_load (GkmSerializable *base,
                         GkmSecret *login,
                         GBytes *data)
{
	GkmXdgTrust *self = GKM_XDG_TRUST (base);
	GNode *asn = NULL;

	if (g_bytes_get_size (data) == 0)
		return FALSE;

	asn = egg_asn1x_create (xdg_asn1_tab, "trust-1");
	g_return_val_if_fail (asn, FALSE);

	if (!egg_asn1x_decode (asn, data)) {
		g_warning ("couldn't parse trust data: %s", egg_asn1x_message (asn));
		egg_asn1x_destroy (asn);
		return FALSE;
	}


	if (!load_assertions (self, asn)) {
		egg_asn1x_destroy (asn);
		return FALSE;
	}


	if (self->pv->bytes)
		g_bytes_unref (self->pv->bytes);
	self->pv->bytes = g_bytes_ref (data);
	egg_asn1x_destroy (self->pv->asn);
	self->pv->asn = asn;

	return TRUE;
}
