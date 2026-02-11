ews_handle_create_folders_param (ESoapParameter *soapparam,
                                 EwsAsyncData *async_data)
{
	ESoapParameter *param, *node;
	EwsFolderId *fid = NULL;
	GSList *fids = NULL;
	const gchar *folder_element;

	switch (async_data->folder_type) {
		case E_EWS_FOLDER_TYPE_MAILBOX:
			folder_element = "Folder";
			break;
		case E_EWS_FOLDER_TYPE_CALENDAR:
			folder_element = "CalendarFolder";
			break;
		case E_EWS_FOLDER_TYPE_CONTACTS:
			folder_element = "ContactsFolder";
			break;
		case E_EWS_FOLDER_TYPE_SEARCH:
			folder_element = "SearchFolder";
			break;
		case E_EWS_FOLDER_TYPE_TASKS:
			folder_element = "TasksFolder";
			break;
		default:
			g_warn_if_reached ();
			folder_element = "Folder";
			break;
	}

	node = e_soap_parameter_get_first_child_by_name (soapparam, "Folders");
	node = e_soap_parameter_get_first_child_by_name (node, folder_element);
	param = e_soap_parameter_get_first_child_by_name (node, "FolderId");

	fid = g_new0 (EwsFolderId, 1);
	fid->id = e_soap_parameter_get_property (param, "Id");
	fid->change_key = e_soap_parameter_get_property (param, "ChangeKey");
	fids = g_slist_append (fids, fid);

	async_data->items_created = fids;
}
