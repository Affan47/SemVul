nm_gconf_set_ip6route_array_helper (GConfClient *client,
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
		GValueArray *elements = (GValueArray *) g_ptr_array_index (value, i);
		GValue *tmp;
		GByteArray *ba;
		guint prefix, metric;
		char dest[INET6_ADDRSTRLEN], next_hop[INET6_ADDRSTRLEN];

		if (   (elements->n_values != 4)
		    || (G_VALUE_TYPE (g_value_array_get_nth (elements, 0)) != DBUS_TYPE_G_UCHAR_ARRAY)
		    || (G_VALUE_TYPE (g_value_array_get_nth (elements, 1)) != G_TYPE_UINT)
		    || (G_VALUE_TYPE (g_value_array_get_nth (elements, 2)) != DBUS_TYPE_G_UCHAR_ARRAY)
		    || (G_VALUE_TYPE (g_value_array_get_nth (elements, 3)) != G_TYPE_UINT))
 {
			g_warning ("%s: invalid IPv6 route!", __func__);
			goto out;
		}

		tmp = g_value_array_get_nth (elements, 0);
		ba = g_value_get_boxed (tmp);
		if (!inet_ntop (AF_INET6, ba->data, dest, sizeof (dest))) {
			g_warning ("%s: invalid IPv6 dest address!", __func__);
			goto out;
		}
		tmp = g_value_array_get_nth (elements, 1);
		prefix = g_value_get_uint (tmp);
		if (prefix > 128) {
			g_warning ("%s: invalid IPv6 dest prefix %u", __func__, prefix);
			goto out;
		}
		tmp = g_value_array_get_nth (elements, 2);
		ba = g_value_get_boxed (tmp);
		if (!inet_ntop (AF_INET6, ba->data, next_hop, sizeof (next_hop))) {
			g_warning ("%s: invalid IPv6 next_hop address!", __func__);
			goto out;
		}
		tmp = g_value_array_get_nth (elements, 3);
		metric = g_value_get_uint (tmp);

		list = g_slist_append (list,
							   g_strdup_printf ("%s/%u,%s,%u", dest, prefix,
												next_hop, metric));
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
