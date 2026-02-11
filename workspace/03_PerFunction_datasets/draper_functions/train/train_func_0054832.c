iscsi_set_targetname(struct iscsi_context *iscsi, const char *target_name)
{
	if (iscsi == NULL) {
		printf("Context is NULL when adding targetname\n");
		return -1;
	}
	if (iscsi->is_loggedin != 0) {
		printf("Already logged in when adding targetname\n");
		return -2;
	}

	if (iscsi->target_name != NULL) {
		free(discard_const(iscsi->target_name));
		iscsi->target_name= NULL;
	}

	iscsi->target_name = strdup(target_name);
	if (iscsi->target_name == NULL) {
		printf("Failed to allocate target name\n");
		return -3;
	}

	return 0;
}
