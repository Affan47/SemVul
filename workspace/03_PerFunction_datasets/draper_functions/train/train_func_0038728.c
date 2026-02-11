pop3_fetch_messages_sync (CamelFolder *folder,
                          CamelFetchType type,
                          gint limit,
                          GCancellable *cancellable,
                          GError **error)
{
	CamelPOP3FolderInfo *fi;
	CamelPOP3Folder *pop3_folder = (CamelPOP3Folder *) folder;
	gint old_len;
	CamelStore *parent_store;
	CamelService *service;
	CamelSettings *settings;
	gint batch_fetch_count;

	parent_store = camel_folder_get_parent_store (folder);
	service = (CamelService *) parent_store;

	settings = camel_service_ref_settings (service);

	batch_fetch_count = camel_pop3_settings_get_batch_fetch_count (
		CAMEL_POP3_SETTINGS (settings));

	g_object_unref (settings);

	old_len = pop3_folder->uids->len;


	fi = pop3_folder->uids->pdata[0];
	if (type == CAMEL_FETCH_OLD_MESSAGES && fi->id == pop3_folder->first_id)
		return FALSE;

	pop3_folder->fetch_type = type;
	pop3_folder->fetch_more = (limit > 0) ? limit : batch_fetch_count;
	pop3_folder_refresh_info_sync (folder, cancellable, error);
	pop3_folder->fetch_more = 0;


	fi = pop3_folder->uids->pdata[0];
	if (type == CAMEL_FETCH_OLD_MESSAGES && fi->id == pop3_folder->first_id)
		return FALSE;
	else if (type == CAMEL_FETCH_NEW_MESSAGES && old_len == pop3_folder->uids->len)
		return FALSE;

	return TRUE;
}
