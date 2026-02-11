ews_append_folder_ids_to_msg (ESoapMessage *msg,
                              const gchar *email,
                              GSList *folder_ids)
{
	GSList *l;

	for (l = folder_ids; l != NULL; l = g_slist_next (l)) {
		const EwsFolderId *fid = l->data;

		ews_append_folder_id_to_msg (msg, email, fid);
	}
}
