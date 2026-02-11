e_book_backend_ews_get_backend_property (EBookBackend *backend,
                                         const gchar *prop_name)
{
	g_return_val_if_fail (prop_name != NULL, NULL);

	if (g_str_equal (prop_name, CLIENT_BACKEND_PROPERTY_CAPABILITIES)) {
		EBookBackendEws *ebews;

		ebews = E_BOOK_BACKEND_EWS (backend);
		g_return_val_if_fail (ebews != NULL, NULL);


		if (ebews->priv->is_gal && !ebews->priv->folder_id) {
			return g_strdup ("net,bulk-removes,contact-lists");
		} else {


			return g_strdup ("net,bulk-removes,do-initial-query,contact-lists");
		}
	} else if (g_str_equal (prop_name, BOOK_BACKEND_PROPERTY_REQUIRED_FIELDS)) {
		return g_strdup (e_contact_field_name (E_CONTACT_FILE_AS));
	} else if (g_str_equal (prop_name, BOOK_BACKEND_PROPERTY_SUPPORTED_FIELDS)) {
		GString *buffer;
		gchar *fields;
		gint ii;

		buffer = g_string_sized_new (1024);

		for (ii = 0; ii < G_N_ELEMENTS (mappings); ii++) {
			if (mappings[ii].element_type != ELEMENT_TYPE_SIMPLE)
				continue;

			if (buffer->len > 0)
				g_string_append_c (buffer, ',');
			g_string_append (buffer, e_contact_field_name (mappings[ii].field_id));
		}

		for (ii = 0; ii < G_N_ELEMENTS (phone_field_map); ii++) {
			if (buffer->len > 0)
				g_string_append_c (buffer, ',');
			g_string_append (buffer, e_contact_field_name (phone_field_map[ii].field));
		}

		fields = g_strjoin (
			",",
			buffer->str,
			e_contact_field_name (E_CONTACT_FULL_NAME),
			e_contact_field_name (E_CONTACT_NICKNAME),
			e_contact_field_name (E_CONTACT_FAMILY_NAME),
			e_contact_field_name (E_CONTACT_EMAIL_1),
			e_contact_field_name (E_CONTACT_EMAIL_2),
			e_contact_field_name (E_CONTACT_EMAIL_3),
			e_contact_field_name (E_CONTACT_ADDRESS_WORK),
			e_contact_field_name (E_CONTACT_ADDRESS_HOME),
			e_contact_field_name (E_CONTACT_ADDRESS_OTHER),
			e_contact_field_name (E_CONTACT_BIRTH_DATE),
			e_contact_field_name (E_CONTACT_NOTE),
			e_contact_field_name (E_CONTACT_PHOTO),
			NULL);

		g_string_free (buffer, TRUE);

		return fields;
	}


	return E_BOOK_BACKEND_CLASS (e_book_backend_ews_parent_class)->
		get_backend_property (backend, prop_name);
}
