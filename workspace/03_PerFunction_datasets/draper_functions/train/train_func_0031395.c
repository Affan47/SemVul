pg_log_v(eLogType type, const char *fmt, va_list ap)
{
	char		message[QUERY_ALLOC];

	vsnprintf(message, sizeof(message), fmt, ap);


	if (((type != PG_VERBOSE && type != PG_STATUS) || log_opts.verbose) &&
		log_opts.internal != NULL)
	{
		if (type == PG_STATUS)

			fprintf(log_opts.internal, "  %s\n", message);
		else
			fprintf(log_opts.internal, "%s", message);
		fflush(log_opts.internal);
	}

	switch (type)
	{
		case PG_VERBOSE:
			if (log_opts.verbose)
				printf("%s", _(message));
			break;

		case PG_STATUS:

			if (isatty(fileno(stdout)))

				printf("  %s%-*.*s\r",

					   strlen(message) <= MESSAGE_WIDTH - 2 ? "" : "...",
					   MESSAGE_WIDTH - 2, MESSAGE_WIDTH - 2,

					   strlen(message) <= MESSAGE_WIDTH - 2 ? message :
					   message + strlen(message) - MESSAGE_WIDTH + 3 + 2);
			else
				printf("  %s\n", _(message));
			break;

		case PG_REPORT:
		case PG_WARNING:
			printf("%s", _(message));
			break;

		case PG_FATAL:
			printf("\n%s", _(message));
			printf("Failure, exiting\n");
			exit(1);
			break;

		default:
			break;
	}
	fflush(stdout);
}
