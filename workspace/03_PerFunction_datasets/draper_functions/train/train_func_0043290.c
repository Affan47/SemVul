parse_cmd (NmCli *nmc, int argc, char **argv)
{
	GError *error = NULL;

	if (argc == 0) {
		if (!nmc_terse_option_check (nmc->print_output, nmc->required_fields, &error))
			goto opt_error;
		nmc->return_value = do_connections_list (nmc, argc, argv);
	} else {

		if (matches (*argv, "list") == 0) {
			nmc->return_value = do_connections_list (nmc, argc-1, argv+1);
		}
		else if (matches(*argv, "status") == 0) {
			if (!nmc_terse_option_check (nmc->print_output, nmc->required_fields, &error))
				goto opt_error;
			nmc->return_value = do_connections_status (nmc, argc-1, argv+1);
		}
		else if (matches(*argv, "up") == 0) {
			nmc->return_value = do_connection_up (nmc, argc-1, argv+1);
		}
		else if (matches(*argv, "down") == 0) {
			nmc->return_value = do_connection_down (nmc, argc-1, argv+1);
		}
		else if (matches(*argv, "delete") == 0) {
			nmc->return_value = do_connection_delete (nmc, argc-1, argv+1);
		}
		else if (   matches (*argv, "help") == 0
		         || (g_str_has_prefix (*argv, "-")  && matches ((*argv)+1, "help") == 0)
		         || (g_str_has_prefix (*argv, "--") && matches ((*argv)+2, "help") == 0)) {
			usage ();
			nmc->should_wait = FALSE;
		}
		else {
			usage ();
			g_string_printf (nmc->return_text, _("Error: 'con' command '%s' is not valid."), *argv);
			nmc->return_value = NMC_RESULT_ERROR_USER_INPUT;
			nmc->should_wait = FALSE;
		}
	}

	return nmc->return_value;

opt_error:
	g_string_printf (nmc->return_text, _("Error: %s."), error->message);
	nmc->return_value = NMC_RESULT_ERROR_USER_INPUT;
	nmc->should_wait = FALSE;
	g_error_free (error);
	return nmc->return_value;
}
