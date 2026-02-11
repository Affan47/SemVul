ews_handle_attachments_param (ESoapParameter *param,
                              EwsAsyncData *async_data)
{
	ESoapParameter *subparam, *attspara;
	EEwsAttachmentInfo *info = NULL;
	EEwsItem *item;
	const gchar *name;

	attspara = e_soap_parameter_get_first_child_by_name (param, "Attachments");

	for (subparam = e_soap_parameter_get_first_child (attspara); subparam != NULL; subparam = e_soap_parameter_get_next_child (subparam)) {
		name = e_soap_parameter_get_name (subparam);

		if (!g_ascii_strcasecmp (name, "ItemAttachment")) {
			item = e_ews_item_new_from_soap_parameter (subparam);
			info = e_ews_item_dump_mime_content (item, async_data->directory);

		} else if (!g_ascii_strcasecmp (name, "FileAttachment")) {
			info = e_ews_dump_file_attachment_from_soap_parameter (
					subparam,
					async_data->directory,
					async_data->sync_state);
		}

		if (info)
			async_data->items = g_slist_append (async_data->items, info);

		info = NULL;
	}
}
