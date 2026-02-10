interpret_date_string(const char *date_opt, time_t * const time_p)
{
	FILE *date_child_fp;
	char date_resp[100];
	const char magic[] = "seconds-into-epoch=";
	char date_command[100];
	int retcode;
	int rc;

	if (date_opt == NULL) {
		warnx(_("No --date option specified."));
		return 14;
	}


	if (strlen(date_opt) > sizeof(date_command) - 50) {
		warnx(_("--date argument too long"));
		return 13;
	}


	if (strchr(date_opt, '"') != NULL) {
		warnx(_
		      ("The value of the --date option is not a valid date.\n"
		       "In particular, it contains quotation marks."));
		return 12;
	}

	sprintf(date_command, "date --date=\"%s\" +seconds-into-epoch=%%s",
		date_opt);
	if (debug)
		printf(_("Issuing date command: %s\n"), date_command);

	date_child_fp = popen(date_command, "r");
	if (date_child_fp == NULL) {
		warn(_("Unable to run 'date' program in /bin/sh shell. "
			    "popen() failed"));
		return 10;
	}

	if (!fgets(date_resp, sizeof(date_resp), date_child_fp))
		date_resp[0] = '\0';
	if (debug)
		printf(_("response from date command = %s\n"), date_resp);
	if (strncmp(date_resp, magic, sizeof(magic) - 1) != 0) {
		warnx(_("The date command issued by %s returned "
				  "unexpected results.\n"
				  "The command was:\n  %s\n"
				  "The response was:\n  %s"),
			program_invocation_short_name, date_command, date_resp);
		retcode = 8;
	} else {
		long seconds_since_epoch;
		rc = sscanf(date_resp + sizeof(magic) - 1, "%ld",
			    &seconds_since_epoch);
		if (rc < 1) {
			warnx(_("The date command issued by %s returned "
				"something other than an integer where the "
				"converted time value was expected.\n"
				"The command was:\n  %s\n"
				"The response was:\n %s\n"),
			      program_invocation_short_name, date_command,
			      date_resp);
			retcode = 6;
		} else {
			retcode = 0;
			*time_p = seconds_since_epoch;
			if (debug)
				printf(_("date string %s equates to "
					 "%ld seconds since 1969.\n"),
				       date_opt, (long)*time_p);
		}
	}
	pclose(date_child_fp);

	return retcode;
}
