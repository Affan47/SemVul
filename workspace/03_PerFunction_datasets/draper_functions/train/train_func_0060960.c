ca_file_foreach_crt (CaFileCallbackFunc func, gboolean view_revoked, gpointer userdata)
{
	gchar *error_str;
        gchar **result;
        guint64 max_id;
        gchar* aux;
        guint num_chars = 1;
        gchar *sql;

        result = __ca_file_get_single_row (ca_db, "SELECT MAX(id) FROM certificates");

        if (result && result[0]) {
		max_id = atoll(result[0]);
		g_strfreev (result);

		aux = g_strdup_printf ("%"G_GUINT64_FORMAT, max_id);
		num_chars = strlen (aux);
		g_free (aux);
	}

	if (view_revoked) {
                sql = sqlite3_mprintf ("SELECT id, is_ca, serial, subject, activation, expiration, revocation, private_key_in_db, pem,"
                                       " dn, parent_dn, parent_route "
				       "FROM certificates ORDER BY concat(zeropad_route(parent_route, %u), zeropad(id, %u)) ",
                                       num_chars, num_chars);
	} else {
                sql = sqlite3_mprintf ("SELECT id, is_ca, serial, subject, activation, expiration, revocation, private_key_in_db, pem, "
                                       " dn, parent_dn, parent_route "
				       "FROM certificates WHERE revocation IS NULL "
                                       "ORDER BY concat(zeropad_route(parent_route, %u), zeropad(id, %u))",
                                       num_chars, num_chars);
	}

        sqlite3_exec (ca_db, sql,
                      func, userdata, &error_str);

        sqlite3_free (sql);

	return  (! error_str);
}
