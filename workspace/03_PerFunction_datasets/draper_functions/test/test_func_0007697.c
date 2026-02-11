e_book_backend_file_upgrade_db (DB *db,
                                gchar *old_version)
{
	gint db_error;
	DBT  version_name_dbt, version_dbt;

	if (!db) {
		g_warning (G_STRLOC ": No DB opened");
		return FALSE;
	}

	if (strcmp (old_version, "0.0")
	    && strcmp (old_version, "0.1")) {
		g_warning (
			"unsupported version '%s' found in PAS backend file\n",
			old_version);
		return FALSE;
	}

	if (!strcmp (old_version, "0.1")) {


		DBT  id_dbt, vcard_dbt;
		DBC *dbc;
		gint  card_failed = 0;

		db_error = db->cursor (db, NULL, &dbc, 0);
		if (db_error != 0) {
			g_warning (G_STRLOC ": db->cursor failed with %s", db_strerror (db_error));
			return FALSE;
		}

		memset (&id_dbt, 0, sizeof (id_dbt));
		memset (&vcard_dbt, 0, sizeof (vcard_dbt));

		db_error = dbc->c_get (dbc, &id_dbt, &vcard_dbt, DB_FIRST);

		while (db_error == 0) {
			if ((id_dbt.size != strlen (E_BOOK_BACKEND_FILE_VERSION_NAME) + 1
			     || strcmp (id_dbt.data, E_BOOK_BACKEND_FILE_VERSION_NAME)) &&
			    (id_dbt.size != strlen (E_BOOK_BACKEND_FILE_REVISION_NAME) + 1
			     || strcmp (id_dbt.data, E_BOOK_BACKEND_FILE_REVISION_NAME))) {
				EContact *contact;

				contact = e_contact_new_from_vcard_with_uid (vcard_dbt.data, id_dbt.data);


				if (strcmp (id_dbt.data, e_contact_get_const (contact, E_CONTACT_UID))) {
					gchar *vcard;

					e_contact_set (contact, E_CONTACT_UID, id_dbt.data);

					vcard = e_vcard_to_string (E_VCARD (contact), EVC_FORMAT_VCARD_30);
					string_to_dbt (vcard, &vcard_dbt);

					db_error = db->put (db, NULL,
							    &id_dbt, &vcard_dbt, 0);

					g_free (vcard);

					if (db_error != 0)
						card_failed++;
				}

				g_object_unref (contact);
			}

			db_error = dbc->c_get (dbc, &id_dbt, &vcard_dbt, DB_NEXT);
		}

		dbc->c_close (dbc);

		if (card_failed) {
			g_warning ("failed to update %d cards", card_failed);
			return FALSE;
		}
	}

	string_to_dbt (E_BOOK_BACKEND_FILE_VERSION_NAME, &version_name_dbt);
	string_to_dbt (E_BOOK_BACKEND_FILE_LAST_BDB_VERSION, &version_dbt);

	db_error = db->put (db, NULL, &version_name_dbt, &version_dbt, 0);
	if (db_error == 0)
		return TRUE;
	else
		return FALSE;
}
