showsmsfolderstatus(gn_data *data, struct gn_statemachine *state)
{
	gn_sms_folder_list folders;
	gn_error error;
	int i;

	memset(&folders, 0, sizeof(folders));
	gn_data_clear(data);
	data->sms_folder_list = &folders;

	if ((error = gn_sm_functions(GN_OP_GetSMSFolders, data, state)) != GN_ERR_NONE) {
		fprintf(stderr, _("Cannot list available folders: %s\n"), gn_error_print(error));
		return error;
	}

	fprintf(stdout, _("No. Name                                         Id #Msg\n"));
	fprintf(stdout, _("========================================================\n"));
	for (i = 0; i < folders.number; i++) {
		data->sms_folder = folders.folder + i;
		if ((error = gn_sm_functions(GN_OP_GetSMSFolderStatus, data, state)) != GN_ERR_NONE) {
			fprintf(stderr, _("Cannot get status of folder \"%s\": %s\n"), folders.folder[i].name, gn_error_print(error));
			return error;
		}
		fprintf(stdout, _("%3d %-42s %4s %4u\n"), i, folders.folder[i].name, gn_memory_type2str(folders.folder_id[i]), folders.folder[i].number);
	}

	return GN_ERR_NONE;
}
