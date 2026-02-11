folder_emit_changed_cb (gpointer user_data)
{
	SignalClosure *signal_closure = user_data;
	CamelFolder *folder;

	folder = g_weak_ref_get (&signal_closure->folder);

	if (folder != NULL) {
		CamelFolderChangeInfo *changes;

		camel_folder_lock (folder, CAMEL_FOLDER_CHANGE_LOCK);
		changes = folder->priv->pending_changes;
		folder->priv->pending_changes = NULL;
		camel_folder_unlock (folder, CAMEL_FOLDER_CHANGE_LOCK);

		g_signal_emit (folder, signals[CHANGED], 0, changes);

		camel_folder_change_info_free (changes);

		g_object_unref (folder);
	}

	return FALSE;
}
