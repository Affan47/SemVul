e_attachment_store_add_to_multipart (EAttachmentStore *store,
                                     CamelMultipart *multipart,
                                     const gchar *default_charset)
{
	GList *list, *iter;

	g_return_if_fail (E_IS_ATTACHMENT_STORE (store));
	g_return_if_fail (CAMEL_MULTIPART (multipart));

	list = e_attachment_store_get_attachments (store);

	for (iter = list; iter != NULL; iter = iter->next) {
		EAttachment *attachment = iter->data;


		if (!e_attachment_get_loading (attachment))
			e_attachment_add_to_multipart (
				attachment, multipart, default_charset);
	}

	g_list_foreach (list, (GFunc) g_object_unref, NULL);
	g_list_free (list);
}
