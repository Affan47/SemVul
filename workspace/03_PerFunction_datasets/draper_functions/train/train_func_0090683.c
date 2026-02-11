e_data_book_respond_get_contact (EDataBook *book,
                                 guint32 opid,
                                 GError *error,
                                 const gchar *vcard)
{
	EBookBackend *backend;
	GSimpleAsyncResult *simple;
	GQueue *queue = NULL;

	g_return_if_fail (E_IS_DATA_BOOK (book));

	backend = e_data_book_ref_backend (book);
	g_return_if_fail (backend != NULL);

	simple = e_book_backend_prepare_for_completion (backend, opid, &queue);
	g_return_if_fail (simple != NULL);
	g_return_if_fail (queue != NULL);


	g_prefix_error (&error, "%s", _("Cannot get contact: "));

	if (error == NULL) {
		EContact *contact;

		contact = e_contact_new_from_vcard (vcard);
		g_queue_push_tail (queue, g_object_ref (contact));
		g_object_unref (contact);
	} else {
		g_simple_async_result_take_error (simple, error);
	}

	g_simple_async_result_complete_in_idle (simple);

	g_object_unref (simple);
	g_object_unref (backend);
}
