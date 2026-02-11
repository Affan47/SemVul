record_auth_for_uri (SoupAuthManagerPrivate *priv, SoupURI *uri,
		     SoupAuth *auth, gboolean prior_auth_failed)
{
	SoupAuthHost *host;
	SoupAuth *old_auth;
	const char *path;
	char *auth_info, *old_auth_info;
	GSList *pspace, *p;

	host = get_auth_host_for_uri (priv, uri);
	auth_info = soup_auth_get_info (auth);

	if (!host->auth_realms) {
		host->auth_realms = soup_path_map_new (g_free);
		host->auths = g_hash_table_new_full (g_str_hash, g_str_equal,
						     g_free, g_object_unref);
	}


	pspace = soup_auth_get_protection_space (auth, uri);
	for (p = pspace; p; p = p->next) {
		path = p->data;
		old_auth_info = soup_path_map_lookup (host->auth_realms, path);
		if (old_auth_info) {
			if (!strcmp (old_auth_info, auth_info))
				continue;
			soup_path_map_remove (host->auth_realms, path);
		}

		soup_path_map_add (host->auth_realms, path,
				   g_strdup (auth_info));
	}
	soup_auth_free_protection_space (auth, pspace);


	old_auth = g_hash_table_lookup (host->auths, auth_info);
	if (old_auth && (old_auth != auth || !prior_auth_failed)) {
		g_free (auth_info);
		return old_auth;
	} else {
		g_hash_table_insert (host->auths, auth_info,
				     g_object_ref (auth));
		return auth;
	}
}
