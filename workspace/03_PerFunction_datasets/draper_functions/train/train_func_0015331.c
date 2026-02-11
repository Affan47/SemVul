insert_stmt_from_contact (EBookBackendSqliteDB *ebsdb,
                          EContact *contact,
                          const gchar *folderid,
                          gboolean store_vcard,
                          gboolean replace_existing,
                          const gchar *default_region)
{
	GString *string;
	gchar *str, *vcard_str;
	gint i;

	str = sqlite3_mprintf (
		"INSERT or %s INTO %Q VALUES (",
		replace_existing ? "REPLACE" : "FAIL", folderid);
	string = g_string_new (str);
	sqlite3_free (str);

	for (i = 0; i < ebsdb->priv->n_summary_fields; i++) {
		if (ebsdb->priv->summary_fields[i].type == G_TYPE_STRING) {
			gchar *val;
			gchar *normal;

			if (i > 0)
				g_string_append (string, ", ");

			val = e_contact_get (contact, ebsdb->priv->summary_fields[i].field);


			if (ebsdb->priv->summary_fields[i].field != E_CONTACT_UID &&
			    ebsdb->priv->summary_fields[i].field != E_CONTACT_REV)
				normal = e_util_utf8_normalize (val);
			else
				normal = g_strdup (val);

			str = sqlite3_mprintf ("%Q", normal);
			g_string_append (string, str);
			sqlite3_free (str);

			if ((ebsdb->priv->summary_fields[i].index & INDEX_SUFFIX) != 0) {
				str = mprintf_suffix (normal);
				g_string_append (string, ", ");
				g_string_append (string, str);
				sqlite3_free (str);
			}

			if ((ebsdb->priv->summary_fields[i].index & INDEX_PHONE) != 0) {
				str = mprintf_phone (normal, default_region);
				g_string_append (string, ", ");
				g_string_append (string, str ? str : "NULL");
				sqlite3_free (str);
			}

			g_free (normal);
			g_free (val);
		} else if (ebsdb->priv->summary_fields[i].type == G_TYPE_BOOLEAN) {
			gboolean val;

			if (i > 0)
				g_string_append (string, ", ");

			val = e_contact_get (contact, ebsdb->priv->summary_fields[i].field) ? TRUE : FALSE;
			g_string_append_printf (string, "%d", val ? 1 : 0);

		} else if (ebsdb->priv->summary_fields[i].type != E_TYPE_CONTACT_ATTR_LIST)
			g_warn_if_reached ();
	}

	vcard_str = store_vcard ? e_vcard_to_string (E_VCARD (contact), EVC_FORMAT_VCARD_30) : NULL;
	str = sqlite3_mprintf (", %Q, %Q)", vcard_str, NULL);

	g_string_append (string, str);

	sqlite3_free (str);
	g_free (vcard_str);

	return g_string_free (string, FALSE);
}
