e_ews_folder_utils_get_source_for_folder (const GList *esources,
                                          const gchar *master_hosturl,
                                          const gchar *master_username,
                                          const gchar *folder_id)
{
	ESource *master_source;
	const GList *iter;

	master_source = e_ews_folder_utils_get_master_source (esources, master_hosturl, master_username);
	if (!master_source)
		return NULL;

	for (iter = esources; iter; iter = iter->next) {
		ESource *source = iter->data;

		if ((is_for_account (source, master_hosturl, master_username) ||
		    g_strcmp0 (e_source_get_uid (master_source), e_source_get_parent (source)) == 0) &&
		    e_source_has_extension (source, E_SOURCE_EXTENSION_EWS_FOLDER)) {
			ESourceEwsFolder *folder_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_EWS_FOLDER);

			g_return_val_if_fail (folder_ext != NULL, NULL);

			if (g_strcmp0 (e_source_ews_folder_get_id (folder_ext), folder_id) == 0)
				return source;
		}
	}

	return NULL;
}
