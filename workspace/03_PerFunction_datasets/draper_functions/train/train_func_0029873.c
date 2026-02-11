qname_to_link (const gchar *qname)
{
	gchar **pieces;
	gchar *name;

	if (NAMESPACES[0].uri) {


		if (g_str_has_prefix (qname, NAMESPACES[0].uri)) {
			pieces = split_qname (qname, NULL);
			name = g_strdup_printf ("#%s", pieces[1]);
			g_strfreev (pieces);
			return name;
		}
	}

	if (class_deffile) {
		gchar *dir, *shortname;
		shortname = qname_to_shortname (qname);
		dir = g_hash_table_lookup (class_deffile, shortname);
		g_free (shortname);
		if (dir) {
			return g_strdup_printf ("../%s/index.html#%s",
			                        dir, qname_to_classname (qname));
		}
	}

	return g_strdup (qname);
}
