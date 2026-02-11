delayed_main(gpointer data)
{
	struct delay_file_data *dfd = (struct delay_file_data *)data;
	if (dfd->log_filename != NULL && strcmp(dfd->log_filename, "") != 0) {
		toplevel_open_log(dfd->top, dfd->log_filename);
	}
	if (dfd->policy_path != NULL) {
		toplevel_open_policy(dfd->top, dfd->policy_path);
	}
	return FALSE;
}
