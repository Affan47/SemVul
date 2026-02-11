camel_folder_summary_add (CamelFolderSummary *summary,
                          CamelMessageInfo *info)
{
	CamelMessageInfoBase *base_info;

	g_return_if_fail (CAMEL_IS_FOLDER_SUMMARY (summary));

	if (info == NULL)
		return;

	camel_folder_summary_lock (summary, CAMEL_FOLDER_SUMMARY_SUMMARY_LOCK);
	if (!summary_assign_uid (summary, info)) {
		camel_folder_summary_unlock (summary, CAMEL_FOLDER_SUMMARY_SUMMARY_LOCK);
		return;
	}

	base_info = (CamelMessageInfoBase *) info;
	folder_summary_update_counts_by_flags (summary, camel_message_info_flags (info), UPDATE_COUNTS_ADD);
	base_info->flags |= CAMEL_MESSAGE_FOLDER_FLAGGED;
	base_info->dirty = TRUE;

	g_hash_table_insert (
		summary->priv->uids,
		(gpointer) camel_pstring_strdup (camel_message_info_uid (info)),
		GUINT_TO_POINTER (camel_message_info_flags (info)));


	g_hash_table_insert (summary->priv->loaded_infos, (gpointer) camel_message_info_uid (info), info);

	camel_folder_summary_touch (summary);

	camel_folder_summary_unlock (summary, CAMEL_FOLDER_SUMMARY_SUMMARY_LOCK);
}
