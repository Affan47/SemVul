maybe_delete_unused_uris (EBookBackendFile *bf,
                          EContact *old_contact,
                          EContact *new_contact)
{
	gchar             *uri_photo, *uri_logo;

	g_return_if_fail (old_contact != NULL);


	uri_photo = check_remove_uri_for_field (old_contact, new_contact, E_CONTACT_PHOTO);
	uri_logo = check_remove_uri_for_field (old_contact, new_contact, E_CONTACT_LOGO);

	if (uri_photo) {
		maybe_delete_uri (bf, uri_photo);
		g_free (uri_photo);
	}

	if (uri_logo) {
		maybe_delete_uri (bf, uri_logo);
		g_free (uri_logo);
	}
}
