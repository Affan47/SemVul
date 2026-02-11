imapx_expunge_uid_from_summary (CamelIMAPXServer *is,
                                gchar *uid,
                                gboolean unsolicited)
{
	CamelFolder *folder;
	CamelIMAPXFolder *ifolder;
	CamelMessageInfo *mi;

	folder = g_weak_ref_get (&is->priv->select_folder);
	g_return_if_fail (folder != NULL);

	ifolder = CAMEL_IMAPX_FOLDER (folder);

	if (unsolicited && ifolder->exists_on_server)
		ifolder->exists_on_server--;

	if (is->priv->changes == NULL)
		is->priv->changes = camel_folder_change_info_new ();

	mi = camel_folder_summary_peek_loaded (folder->summary, uid);
	if (mi) {
		camel_folder_summary_remove (folder->summary, mi);
		camel_message_info_free (mi);
	} else {
		camel_folder_summary_remove_uid (folder->summary, uid);
	}

	camel_folder_change_info_remove_uid (is->priv->changes, uid);

	if (imapx_in_idle (is)) {
		camel_folder_summary_save_to_db (folder->summary, NULL);
		imapx_update_store_summary (folder);
		camel_folder_changed (folder, is->priv->changes);

		camel_folder_change_info_clear (is->priv->changes);
	}

	g_object_unref (folder);
}
