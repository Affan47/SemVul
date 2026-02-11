save_assertions (GkmXdgTrust *self, GNode *asn)
{
	GHashTableIter iter;
	GNode *pair, *node;
	gpointer value;

	g_assert (GKM_XDG_IS_TRUST (self));
	g_assert (asn);

	node = egg_asn1x_node (asn, "assertions", NULL);
	egg_asn1x_clear (node);

	g_hash_table_iter_init (&iter, self->pv->assertions);
	while (g_hash_table_iter_next (&iter, NULL, &value)) {
		pair = egg_asn1x_append (node);
		g_return_val_if_fail (pair, FALSE);
		save_assertion (pair, GKM_ASSERTION (value));
	}

	return TRUE;
}
