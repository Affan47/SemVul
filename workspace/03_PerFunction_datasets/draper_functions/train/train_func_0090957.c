deletealltodos(gn_data *data, struct gn_statemachine *state)
{
	gn_error error;

	gn_data_clear(data);

	error = gn_sm_functions(GN_OP_DeleteAllToDos, data, state);
	if (error == GN_ERR_NONE)
		fprintf(stderr, _("Successfully deleted all ToDo notes!\n"));
	else
		fprintf(stderr, _("Failed to delete ToDo note: %s\n"), gn_error_print(error));
	return error;
}
