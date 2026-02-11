file_util_start_editor_full(const gchar *key, FileData *source_fd, GList *flist, const gchar *dest_path, const gchar *working_directory, GtkWidget *parent, UtilityPhase phase)
{
	UtilityData *ud;
	GList *ungrouped = NULL;

	if (editor_no_param(key))
		{
		gchar *file_directory = NULL;
		if (!working_directory)
			{

			if (source_fd)
				file_directory = remove_level_from_path(source_fd->path);

			if (!file_directory && flist)
				file_directory = remove_level_from_path(((FileData *)flist->data)->path);
			working_directory = file_directory;
			}


		start_editor(key, working_directory);
		g_free(file_directory);
		filelist_free(flist);
		return;
		}


	if (source_fd)
		{


		flist = g_list_concat(filelist_copy(source_fd->sidecar_files), flist);
		flist = g_list_append(flist, file_data_ref(source_fd));
		}

	if (!flist) return;

	if (file_util_write_metadata_first(UTILITY_TYPE_FILTER, phase, flist, dest_path, key, parent))
		return;

	flist = file_data_process_groups_in_selection(flist, TRUE, &ungrouped);

	if (!file_data_sc_add_ci_unspecified_list(flist, dest_path))
		{
		file_util_warn_op_in_progress(_("Can't run external editor"));
		file_data_disable_grouping_list(ungrouped, FALSE);
		filelist_free(flist);
		filelist_free(ungrouped);
		return;
		}

	file_util_mark_ungrouped_files(ungrouped);
	filelist_free(ungrouped);

	if (editor_is_filter(key))
		ud = file_util_data_new(UTILITY_TYPE_FILTER);
	else
		ud = file_util_data_new(UTILITY_TYPE_EDITOR);


	if (ud->type == UTILITY_TYPE_FILTER && dest_path == NULL) phase = UTILITY_PHASE_START;

	ud->phase = phase;

	ud->with_sidecars = TRUE;

	ud->external_command = g_strdup(key);

	ud->dir_fd = NULL;
	ud->flist = flist;
	ud->content_list = NULL;
	ud->parent = parent;

	ud->details_func = file_util_details_dialog;

	if (dest_path) ud->dest_path = g_strdup(dest_path);

	ud->messages.title = _("Editor");
	ud->messages.question = _("Run editor?");
	ud->messages.desc_flist = _("This will copy the following files");
	ud->messages.desc_source_fd = "";
	ud->messages.fail = _("External command failed");

	file_util_dialog_run(ud);
}
