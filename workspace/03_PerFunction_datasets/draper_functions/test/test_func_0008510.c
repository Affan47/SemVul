camel_ews_utils_create_mime_message (EEwsConnection *cnc,
                                     const gchar *disposition,
                                     const EwsFolderId *fid,
                                     CamelMimeMessage *message,
                                     CamelMessageInfo *info,
                                     CamelAddress *from,
				     CamelAddress *recipients,
                                     gchar **itemid,
                                     gchar **changekey,
                                     GCancellable *cancellable,
                                     GError **error)
{
	struct _create_mime_msg_data *create_data;
	GSList *ids;
	EEwsItem *item;
	const EwsId *ewsid;
	gchar *restore_from = NULL;
	gboolean res;

	create_data = g_new0 (struct _create_mime_msg_data, 1);

	create_data->message = message;
	create_data->info = info;
	create_data->from = from;
	create_data->recipients = recipients;

	if (g_strcmp0 (disposition, "SendOnly") == 0 ||
	    g_strcmp0 (disposition, "SendAndSaveCopy") == 0) {
		struct _camel_header_raw *header;

		for (header = CAMEL_MIME_PART (message)->headers; header; header = header->next) {
			if (header->name && g_ascii_strcasecmp (header->name, "From") == 0) {
				restore_from = header->value;
				header->value = g_strdup ("");
				break;
			}
		}
	}

	res = e_ews_connection_create_items_sync (
		cnc, EWS_PRIORITY_MEDIUM,
		disposition, NULL, fid,
		create_mime_message_cb, create_data,
		&ids, cancellable, error);

	if (restore_from) {
		struct _camel_header_raw *header;

		for (header = CAMEL_MIME_PART (message)->headers; header; header = header->next) {
			if (header->name && g_ascii_strcasecmp (header->name, "From") == 0) {
				g_free (header->value);
				header->value = restore_from;
				break;
			}
		}
	}

	if (!res || (!itemid && !changekey))
		return res;

	item = (EEwsItem *) ids->data;
	if (!item || !(ewsid = e_ews_item_get_id (item))) {
		g_set_error (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("CreateItem call failed to return ID for new message"));
		return FALSE;
	}

	if (itemid)
		*itemid = g_strdup (ewsid->id);
	if (changekey)
		*changekey = g_strdup (ewsid->change_key);

	g_object_unref (item);
	g_slist_free (ids);
	return TRUE;
}
