_add_it (int argc, char *argv[])
{
	int error_code = SLURM_SUCCESS;
	int command_len = 0;

	if (readonly_flag) {
		exit_code = 1;
		fprintf(stderr, "Can't run this command in readonly mode.\n");
		return;
	}

	if (!argv[0])
		goto helpme;

	command_len = strlen(argv[0]);

	acct_storage_g_commit(db_conn, 0);


	if (strncasecmp (argv[0], "Account", MAX(command_len, 1)) == 0
	    || !strncasecmp (argv[0], "Acct", MAX(command_len, 4))) {
		error_code = sacctmgr_add_account((argc - 1), &argv[1]);
	} else if (strncasecmp (argv[0], "Cluster", MAX(command_len, 2)) == 0) {
		error_code = sacctmgr_add_cluster((argc - 1), &argv[1]);
	} else if (strncasecmp (argv[0], "Coordinator",
				MAX(command_len, 2)) == 0) {
		error_code = sacctmgr_add_coord((argc - 1), &argv[1]);
	} else if (strncasecmp (argv[0], "QOS", MAX(command_len, 1)) == 0) {
		error_code = sacctmgr_add_qos((argc - 1), &argv[1]);
	} else if (strncasecmp (argv[0], "User", MAX(command_len, 1)) == 0) {
		error_code = sacctmgr_add_user((argc - 1), &argv[1]);
	} else {
	helpme:
		exit_code = 1;
		fprintf(stderr, "No valid entity in add command\n");
		fprintf(stderr, "Input line must include, ");
		fprintf(stderr, "\"Account\", \"Cluster\", \"Coordinator\", ");
		fprintf(stderr, "\"QOS\", or \"User\"\n");
	}

	if (error_code != SLURM_SUCCESS) {
		exit_code = 1;
	}
}
