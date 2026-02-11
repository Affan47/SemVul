format_urn (GHashTable  *prefixes,
            const gchar *urn,
            gboolean     full_namespaces)
{
	gchar *urn_out;

	if (full_namespaces) {
		urn_out = g_strdup_printf ("<%s>", urn);
	} else {
		gchar *shorthand = get_shorthand (prefixes, urn);


		if (g_strcmp0 (shorthand, urn) == 0) {
			urn_out = g_strdup_printf ("<%s>", urn);
			g_free (shorthand);
		} else {
			urn_out = shorthand;
		}
	}

	return urn_out;
}
