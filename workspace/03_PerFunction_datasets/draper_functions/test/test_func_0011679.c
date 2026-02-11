main(int argc, char *argv[])
{
	char *action_type     = NULL;
	int status = 1;

	fprintf(stdout, "Content-type: text/html\n\n");

	if ( init_ds_env() )
		return 1;

	action_type = get_cgi_var("ACTION", "Missing Command",
								   "Need to specify Start, Stop, or Restart");
	if (!action_type)
		return 1;

	if (!strcmp(action_type, "START")) {
		status = nsldapagt_start();
	} else if (!strcmp(action_type, "STOP")) {
		status = nsldapagt_shutdown();
	} else if (!strcmp(action_type, "RESTART")) {
		status = nsldapagt_restart();
	} else {
		status = DS_UNKNOWN_SNMP_COMMAND;
	}

	if ( !status ) {
		rpt_success("Success!");
		return 0;
	} else {
		rpt_err( status, action_type, NULL,  NULL );
		return 1;
	}
}
