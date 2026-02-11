vee_folder_remove_unmatched (CamelVeeFolder *vfolder,
                             CamelVeeSummary *vsummary,
                             CamelVeeDataCache *data_cache,
                             CamelFolderChangeInfo *changes,
                             CamelFolder *subfolder,
                             const gchar *orig_message_uid,
                             gboolean is_orig_message_uid)

{
	CamelVeeMessageInfoData *mi_data;

	if (is_orig_message_uid) {


		if (!camel_vee_data_cache_contains_message_info_data (data_cache, subfolder, orig_message_uid))
			return;

		mi_data = camel_vee_data_cache_get_message_info_data (data_cache, subfolder, orig_message_uid);
	} else
		mi_data = camel_vee_data_cache_get_message_info_data_by_vuid (data_cache, orig_message_uid);

	if (!mi_data)
		return;

	vee_folder_note_unmatch_uid (vfolder, vsummary, subfolder, data_cache, mi_data, changes);

	g_object_unref (mi_data);
}
