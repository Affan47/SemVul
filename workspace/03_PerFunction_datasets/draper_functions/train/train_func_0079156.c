deletefilebyid(char *id, gn_data *data, struct gn_statemachine *state)
{
    	gn_file fi;
	gn_error error;

	memset(&fi, 0, sizeof(fi));
	set_fileid(&fi, id);

	gn_data_clear(data);
	data->file = &fi;

	if ((error = gn_sm_functions(GN_OP_DeleteFileById, data, state)) != GN_ERR_NONE)
		fprintf(stderr, _("Failed to delete %s: %s\n"), id, gn_error_print(error));
	else {
		fprintf(stderr, _("Deleted: %s\n"), id);
	}
	return error;
}
