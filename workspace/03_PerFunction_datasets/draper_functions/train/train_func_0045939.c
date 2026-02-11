minivm_delete_exec(struct ast_channel *chan, const char *data)
{
	int res = 0;
	char filename[BUFSIZ];

	if (!ast_strlen_zero(data)) {
		ast_copy_string(filename, (char *) data, sizeof(filename));
	} else {
		ast_channel_lock(chan);
		ast_copy_string(filename, pbx_builtin_getvar_helper(chan, "MVM_FILENAME"), sizeof(filename));
		ast_channel_unlock(chan);
	}

	if (ast_strlen_zero(filename)) {
		ast_log(LOG_ERROR, "No filename given in application arguments or channel variable MVM_FILENAME\n");
		return res;
	}


	if (ast_fileexists(filename, NULL, NULL) > 0) {
		res = vm_delete(filename);
		if (res) {
			ast_debug(2, "Can't delete file: %s\n", filename);
			pbx_builtin_setvar_helper(chan, "MVM_DELETE_STATUS", "FAILED");
		} else {
			ast_debug(2, "Deleted voicemail file :: %s \n", filename);
			pbx_builtin_setvar_helper(chan, "MVM_DELETE_STATUS", "SUCCESS");
		}
	} else {
		ast_debug(2, "Filename does not exist: %s\n", filename);
		pbx_builtin_setvar_helper(chan, "MVM_DELETE_STATUS", "FAILED");
	}

	return res;
}
