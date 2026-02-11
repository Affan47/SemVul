hard_link_photo (EBookBackendFile *bf,
                 EContact *contact,
                 EContactField field,
                 const gchar *src_filename,
                 GError **error)
{
	gchar *fullname = NULL, *name, *str;
	gint   i = 0, ret;
	const gchar *suffix;


	suffix = strrchr (src_filename, '.');
	if (suffix)
		suffix++;

	if (!suffix)
		suffix = "data";


	name = g_strconcat (
		e_contact_get_const (contact, E_CONTACT_UID), "_",
		e_contact_field_name (field), NULL);
	name = g_strdelimit (name, NULL, '_');

	do {
		g_free (fullname);

		str = e_filename_mkdir_encoded (bf->priv->photo_dirname, name, NULL, i);
		fullname = g_strdup_printf ("%s.%s", str, suffix);
		g_free (str);

		i++;

		ret = link (src_filename, fullname);

	} while (ret < 0 && errno == EEXIST);

	if (ret < 0) {
		if (errno == EACCES || errno == EPERM) {
			g_set_error_literal (
				error, E_CLIENT_ERROR,
				E_CLIENT_ERROR_PERMISSION_DENIED,
				e_client_error_to_string (
				E_CLIENT_ERROR_PERMISSION_DENIED));
		} else {
			g_set_error (
				error, E_CLIENT_ERROR,
				E_CLIENT_ERROR_OTHER_ERROR,
				_("Failed to create hardlink for resource '%s': %s"),
				src_filename, g_strerror (errno));
		}
		g_free (fullname);
		fullname = NULL;
	}

	g_free (name);

	return fullname;
}
