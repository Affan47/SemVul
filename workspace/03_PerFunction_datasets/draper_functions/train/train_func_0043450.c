action_show_all_cb (GtkAction *action,
                    EAttachmentView *view)
{
	EAttachmentStore *store;
	GList *list, *iter;

	store = e_attachment_view_get_store (view);
	list = e_attachment_store_get_attachments (store);

	for (iter = list; iter != NULL; iter = iter->next) {
		EAttachment *attachment;

		attachment = E_ATTACHMENT (iter->data);
		e_attachment_set_shown (attachment, TRUE);
	}

	g_list_foreach (list, (GFunc) g_object_unref, NULL);
	g_list_free (list);
}
