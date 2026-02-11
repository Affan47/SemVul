e_book_add_contact (EBook *book,
                    EContact *contact,
                    GError **error)
{
	gchar *added_uid = NULL;
	gboolean success;

	g_return_val_if_fail (E_IS_BOOK (book), FALSE);
	g_return_val_if_fail (E_IS_CONTACT (contact), FALSE);

	success = e_book_client_add_contact_sync (
		book->priv->client, contact, &added_uid, NULL, error);

	if (added_uid != NULL) {
		e_contact_set (contact, E_CONTACT_UID, added_uid);
		g_free (added_uid);
	}

	return success;
}
