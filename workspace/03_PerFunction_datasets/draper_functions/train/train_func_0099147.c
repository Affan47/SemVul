lookup_or_create_assertion_key (GkmAssertion *assertion)
{
	GBytes *key;

	key = lookup_assertion_key (assertion);
	if (key == NULL) {
		key = create_assertion_key (gkm_assertion_get_purpose (assertion),
		                            gkm_assertion_get_peer (assertion));
		g_object_set_qdata_full (G_OBJECT (assertion), QDATA_ASSERTION_KEY,
		                         g_bytes_ref (key), (GDestroyNotify)g_bytes_unref);
	}

	return key;
}
