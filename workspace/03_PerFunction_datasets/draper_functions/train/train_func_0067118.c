adcli_tool_group_delete (adcli_conn *conn,
                         int argc,
                         char *argv[])
{
	adcli_result res;
	adcli_entry *entry;
	int opt;

	struct option options[] = {
		{ "domain", required_argument, NULL, opt_domain },
		{ "domain-realm", required_argument, NULL, opt_domain_realm },
		{ "domain-controller", required_argument, NULL, opt_domain_controller },
		{ "login-user", required_argument, NULL, opt_login_user },
		{ "login-ccache", optional_argument, NULL, opt_login_ccache },
		{ "no-password", no_argument, 0, opt_no_password },
		{ "stdin-password", no_argument, 0, opt_stdin_password },
		{ "prompt-password", no_argument, 0, opt_prompt_password },
		{ "verbose", no_argument, NULL, opt_verbose },
		{ "help", no_argument, NULL, 'h' },
		{ 0 },
	};

	static adcli_tool_desc usages[] = {
		{ 0, "usage: adcli delete-group --domain=xxxx group" },
		{ 0 },
	};

	while ((opt = adcli_tool_getopt (argc, argv, options)) != -1) {
		switch (opt) {
		case 'h':
		case '?':
		case ':':
			adcli_tool_usage (options, usages);
			adcli_tool_usage (options, common_usages);
			return opt == 'h' ? 0 : 2;
		default:
			parse_option ((Option)opt, optarg, conn);
			break;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1)
		errx (2, "specify one group name to delete");

	entry = adcli_entry_new_group (conn, argv[0]);
	if (entry == NULL)
		errx (-1, "unexpected memory problems");

	adcli_conn_set_allowed_login_types (conn, ADCLI_LOGIN_USER_ACCOUNT);

	res = adcli_conn_connect (conn);
	if (res != ADCLI_SUCCESS) {
		errx (-res, "couldn't connect to %s domain: %s",
		      adcli_conn_get_domain_name (conn),
		      adcli_get_last_error ());
	}

	res = adcli_entry_delete (entry);
	if (res != ADCLI_SUCCESS) {
		errx (-res, "deleting group %s in domain %s failed: %s",
		      adcli_entry_get_sam_name (entry),
		      adcli_conn_get_domain_name (conn),
		      adcli_get_last_error ());
	}

	adcli_entry_unref (entry);

	return 0;
}
