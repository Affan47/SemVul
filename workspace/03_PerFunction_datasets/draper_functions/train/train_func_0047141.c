nm_gconf_set_ip6dns_array_helper (GConfClient *client,
								  const char *path,
								  const char *key,
								  const char *setting,
								  GPtrArray *value)
{
	char *gc_key;
	int i;
	GSList *list = NULL, *l;
	gboolean success = FALSE;

	g_return_val_if_fail (key != NULL, FALSE);
	g_return_val_if_fail (setting != NULL, FALSE);

	if (!value)
		return TRUE;

	gc_key = g_strdup_printf ("%s/%s/%s", path, setting, key);
	if (!gc_key) {
		g_warning ("Not enough memory to create gconf path");
		return FALSE;
	}

	for (i = 0; i < value->len; i++) {
		GByteArray *ba = g_ptr_array_index (value, i);
		char addr[INET6_ADDRSTRLEN];

		if (!inet_ntop (AF_INET6, ba->data, addr, sizeof (addr))) {
			g_warning ("%s: invalid IPv6 DNS server address!", __func__);
			goto out;
		}

		list = g_slist_append (list, g_strdup (addr));
	}

	gconf_client_set_list (client, gc_key, GCONF_VALUE_STRING, list, NULL);
	success = TRUE;

out:
	for (l = list; l; l = l->next)
		g_free (l->data);
	g_slist_free (list);
	g_free (gc_key);
	return success;
}
