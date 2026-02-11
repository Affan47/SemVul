get_photo (EBookBackendEws *ebews,
	   EEwsItem *item,
	   GCancellable *cancellable,
	   GError **error)
{
	EContactPhoto *photo = NULL;
	EEwsAttachmentInfo *info;
	GSList *contact_item_ids = NULL, *new_items = NULL;
	GSList *attachments = NULL,  *attachments_ids = NULL;
	const guchar *content;
	const gchar *contact_photo_id;
	const EwsId *id;
	gsize len;

	id = e_ews_item_get_id (item);
	contact_item_ids = g_slist_prepend (contact_item_ids, g_strdup (id->id));
	if (!e_ews_connection_get_items_sync (
			ebews->priv->cnc,
			EWS_PRIORITY_MEDIUM,
			contact_item_ids,
			"IdOnly",
			"item:Attachments",
			FALSE,
			NULL,
			E_EWS_BODY_TYPE_TEXT,
			&new_items,
			NULL,
			NULL,
			cancellable,
			error))
		goto exit;

	contact_photo_id = e_ews_item_get_contact_photo_id (new_items->data);
	if (!contact_photo_id)
		goto exit;

	attachments_ids = g_slist_prepend (attachments_ids, g_strdup (contact_photo_id));
	if (!e_ews_connection_get_attachments_sync (
		ebews->priv->cnc,
		EWS_PRIORITY_MEDIUM,
		NULL,
		attachments_ids,
		NULL,
		FALSE,
		&attachments,
		NULL,
		NULL,
		cancellable,
		error))
		goto exit;

	info = attachments->data;
	content = (guchar *) e_ews_attachment_info_get_inlined_data (info, &len);

	photo = e_contact_photo_new ();
	photo->type = E_CONTACT_PHOTO_TYPE_INLINED;
	e_contact_photo_set_inlined (photo, content, len);

exit:
	g_slist_free_full (contact_item_ids, g_free);
	g_slist_free_full (new_items, g_object_unref);
	g_slist_free_full (attachments_ids, g_free);
	g_slist_free_full (attachments, (GDestroyNotify) e_ews_attachment_info_free);

	return photo;
}
