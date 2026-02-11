ebews_set_photo_changes (EBookBackendEws *ebews,
			 ESoapMessage *message,
			 EContact *new,
			 EContact *old,
			 GCancellable *cancellable,
			 GError **error)
{
	EContactPhoto *old_photo, *new_photo;
	GSList *contact_item_ids = NULL, *new_items = NULL, *attachments_ids = NULL;
	gchar *id = e_contact_get (old, E_CONTACT_UID);
	const gchar *contact_photo_id;


	if (!e_ews_connection_satisfies_server_version (ebews->priv->cnc, E_EWS_EXCHANGE_2010_SP2))
		return;

	old_photo = e_contact_get (old, E_CONTACT_PHOTO);
	new_photo = e_contact_get (new, E_CONTACT_PHOTO);

	if (photos_equal (old_photo, new_photo))
		goto exit;

	contact_item_ids = g_slist_append (contact_item_ids, id);
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
	if (contact_photo_id) {
		attachments_ids = g_slist_prepend (attachments_ids, g_strdup (contact_photo_id));
		if (!e_ews_connection_delete_attachments_sync (
					ebews->priv->cnc,
					EWS_PRIORITY_MEDIUM,
					attachments_ids,
					NULL,
					cancellable,
					error))
			goto exit;
	}

	if (new_photo)
		set_photo (ebews, new, new_photo, cancellable, error);

exit:
	e_contact_photo_free (old_photo);
	e_contact_photo_free (new_photo);
	g_slist_free_full (contact_item_ids, g_free);
	g_slist_free_full (new_items, g_object_unref);
	g_slist_free_full (attachments_ids, g_free);
}
