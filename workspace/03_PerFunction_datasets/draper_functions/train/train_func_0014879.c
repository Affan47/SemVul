update_restore_from_trash_action (GtkAction *action,
				  GList *files,
				  gboolean is_self)
{
	NemoFile *original_file;
	NemoFile *original_dir;
	GHashTable *original_dirs_hash;
	GList *original_dirs;
	GFile *original_location;
	char *tooltip, *original_name;

	original_file = NULL;
	original_dir = NULL;
	original_dirs = NULL;
	original_dirs_hash = NULL;
	original_location = NULL;
	original_name = NULL;

	if (files != NULL) {
		if (g_list_length (files) == 1) {
			original_file = nemo_file_get_trash_original_file (files->data);
		} else {
			original_dirs_hash = nemo_trashed_files_get_original_directories (files, NULL);
			if (original_dirs_hash != NULL) {
				original_dirs = g_hash_table_get_keys (original_dirs_hash);
				if (g_list_length (original_dirs) == 1) {
					original_dir = nemo_file_ref (NEMO_FILE (original_dirs->data));
				}
			}
		}
	}

	if (original_file != NULL || original_dirs != NULL) {
		gtk_action_set_visible (action, TRUE);

		if (original_file != NULL) {
			original_location = nemo_file_get_location (original_file);
		} else if (original_dir != NULL) {
			original_location = nemo_file_get_location (original_dir);
		}

		if (original_location != NULL) {
			original_name = g_file_get_parse_name (original_location);
		}

		if (is_self) {
			g_assert (g_list_length (files) == 1);
			g_assert (original_location != NULL);
			tooltip = g_strdup_printf (_("Move the open folder out of the trash to \"%s\""), original_name);
		} else if (files_are_all_directories (files)) {
			if (original_name != NULL) {
				tooltip = g_strdup_printf (ngettext ("Move the selected folder out of the trash to \"%s\"",
								     "Move the selected folders out of the trash to \"%s\"",
								     g_list_length (files)), original_name);
			} else {
				tooltip = g_strdup_printf (ngettext ("Move the selected folder out of the trash",
								     "Move the selected folders out of the trash",
								     g_list_length (files)));
			}
		} else if (files_is_none_directory (files)) {
			if (original_name != NULL) {
				tooltip = g_strdup_printf (ngettext ("Move the selected file out of the trash to \"%s\"",
								     "Move the selected files out of the trash to \"%s\"",
								     g_list_length (files)), original_name);
			} else {
				tooltip = g_strdup_printf (ngettext ("Move the selected file out of the trash",
								     "Move the selected files out of the trash",
								     g_list_length (files)));
			}
		} else {
			if (original_name != NULL) {
				tooltip = g_strdup_printf (ngettext ("Move the selected item out of the trash to \"%s\"",
								     "Move the selected items out of the trash to \"%s\"",
								     g_list_length (files)), original_name);
			} else {
				tooltip = g_strdup_printf (ngettext ("Move the selected item out of the trash",
								     "Move the selected items out of the trash",
								     g_list_length (files)));
			}
		}
		g_free (original_name);

		g_object_set (action, "tooltip", tooltip, NULL);
		g_free (tooltip);

		if (original_location != NULL) {
			g_object_unref (original_location);
		}
	} else {
		gtk_action_set_visible (action, FALSE);
	}

	nemo_file_unref (original_file);
	nemo_file_unref (original_dir);
	g_list_free (original_dirs);

	if (original_dirs_hash != NULL) {
		g_hash_table_destroy (original_dirs_hash);
	}
}
