sieve_notify(void *ac,
			void *interp_context __attribute__((unused)),
			void *script_context,
			void *mc __attribute__((unused)),
			const char **errmsg __attribute__((unused)))
{
    const char *notifier = config_getstring(IMAPOPT_SIEVENOTIFIER);

    if (notifier) {
	sieve_notify_context_t *nc = (sieve_notify_context_t *) ac;
	script_data_t *sd = (script_data_t *) script_context;
	int nopt = 0;

	snmp_increment(SIEVE_NOTIFY, 1);


	while (nc->options[nopt]) nopt++;


	notify(!strcmp("default",nc->method) ? notifier : nc->method,
	       "SIEVE", nc->priority, sd->username, NULL,
	       nopt, nc->options, nc->message);
    }

    return SIEVE_OK;
}
