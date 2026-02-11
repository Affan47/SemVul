e_book_backend_cache_get_contact (EBookBackendCache *cache,
                                  const gchar *uid)
{
	const gchar *vcard_str;
	EContact *contact = NULL;

	g_return_val_if_fail (E_IS_BOOK_BACKEND_CACHE (cache), NULL);
	g_return_val_if_fail (uid != NULL, NULL);

	vcard_str = e_file_cache_get_object (E_FILE_CACHE (cache), uid);
	if (vcard_str) {
		contact = e_contact_new_from_vcard_with_uid (vcard_str, uid);

	}

	return contact;
}
