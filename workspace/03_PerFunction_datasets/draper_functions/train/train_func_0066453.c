_dmap_share_name_collision (DMAPShare * share,
			    DMAPMdnsPublisher * publisher, const char *name)
{
	char *new_name = "FIXME";

	if (share->priv->name == NULL || name == NULL) {
		return;
	}

	if (strcmp (share->priv->name, name) == 0) {
		g_warning ("Duplicate share name on mDNS");

		_dmap_share_set_name (DMAP_SHARE (share), new_name);
		g_free (new_name);
	}

	return;
}
