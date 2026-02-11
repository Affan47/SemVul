e_ews_folder_utils_populate_esource (ESource *source,
                                     const GList *sources,
                                     const gchar *master_hosturl,
                                     const gchar *master_username,
                                     EEwsFolder *folder,
				     EEwsESourceFlags flags,
                                     gint color_seed,
                                     GCancellable *cancellable,
                                     GError **perror)
{
	ESource *master_source;
	gboolean res = FALSE;

	master_source = e_ews_folder_utils_get_master_source (sources, master_hosturl, master_username);

	if (master_source) {
		ESourceBackend *backend_ext;
		EEwsFolderType folder_type;
		const EwsFolderId *folder_id = e_ews_folder_get_id (folder);

		g_return_val_if_fail (folder_id != NULL, FALSE);

		folder_type = e_ews_folder_get_folder_type (folder);

		e_source_set_parent (source, e_source_get_uid (master_source));
		e_source_set_display_name (source, e_ews_folder_get_name (folder));

		switch (folder_type) {
			case E_EWS_FOLDER_TYPE_CALENDAR:
				backend_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_CALENDAR);
				break;
			case E_EWS_FOLDER_TYPE_MEMOS:
				backend_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_MEMO_LIST);
				break;
			case E_EWS_FOLDER_TYPE_TASKS:
				backend_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_TASK_LIST);
				break;
			case E_EWS_FOLDER_TYPE_CONTACTS:
				backend_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_ADDRESS_BOOK);
				break;
			default:
				backend_ext = NULL;
				break;
		}

		if (backend_ext) {
			ESourceEwsFolder *folder_ext;
			ESourceOffline *offline_ext;

			e_source_backend_set_backend_name (backend_ext, "ews");

			folder_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_EWS_FOLDER);
			e_source_ews_folder_set_id (folder_ext, folder_id->id);
			e_source_ews_folder_set_change_key (folder_ext, NULL);
			e_source_ews_folder_set_foreign (folder_ext, e_ews_folder_get_foreign (folder));
			e_source_ews_folder_set_foreign_subfolders (folder_ext, (flags & E_EWS_ESOURCE_FLAG_INCLUDE_SUBFOLDERS) != 0);
			e_source_ews_folder_set_public (folder_ext, (flags & E_EWS_ESOURCE_FLAG_PUBLIC_FOLDER) != 0);

			offline_ext = e_source_get_extension (source, E_SOURCE_EXTENSION_OFFLINE);
			e_source_offline_set_stay_synchronized (offline_ext, (flags & E_EWS_ESOURCE_FLAG_OFFLINE_SYNC) != 0);


			if (folder_type != E_EWS_FOLDER_TYPE_CONTACTS) {
				ESourceAlarms *alarms;
				gchar *color_str;

				color_str = e_ews_folder_utils_pick_color_spec (
					1 + g_list_length ((GList *) sources),
					folder_type != E_EWS_FOLDER_TYPE_CALENDAR);
				e_source_selectable_set_color (E_SOURCE_SELECTABLE (backend_ext), color_str);
				g_free (color_str);

				alarms = e_source_get_extension (source, E_SOURCE_EXTENSION_ALARMS);
				e_source_alarms_set_include_me (alarms, FALSE);
			}

			res = TRUE;
		} else {
			g_propagate_error (
				perror, g_error_new_literal (EWS_CONNECTION_ERROR,
				EWS_CONNECTION_ERROR_NORESPONSE, _("Cannot add folder, unsupported folder type")));
		}
	} else {
		g_propagate_error (
			perror, g_error_new_literal (EWS_CONNECTION_ERROR,
			EWS_CONNECTION_ERROR_NORESPONSE, _("Cannot add folder, master source not found")));
	}

	return res;
}
