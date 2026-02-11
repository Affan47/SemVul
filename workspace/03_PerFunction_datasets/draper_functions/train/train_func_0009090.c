prep_chain_private (GcrCertificateChainPrivate *orig, const gchar *purpose,
                    const gchar *peer, guint flags)
{
	GcrCertificateChainPrivate *pv;
	GcrCertificate *certificate;
	guint i;

	g_assert (orig);
	g_assert (purpose);

	pv = new_chain_private ();
	for (i = 0; i < orig->certificates->len; ++i) {
		certificate = g_ptr_array_index (orig->certificates, i);
		g_ptr_array_add (pv->certificates, g_object_ref (certificate));
	}

	pv->status = orig->status;
	pv->purpose = g_strdup (purpose);
	pv->peer = g_strdup (peer);
	pv->flags = flags;
	return pv;
}
