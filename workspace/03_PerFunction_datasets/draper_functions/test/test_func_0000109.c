write_failover_state (dhcp_failover_state_t *state)
{
	int errors = 0;
	const char *tval;

	if (lease_file_is_corrupt)
		if (!new_lease_file ())
			return 0;

	errno = 0;
	fprintf (db_file, "\nfailover peer \"%s\" state {", state -> name);
	if (errno)
		++errors;

	tval = print_time(state->me.stos);
	if (tval == NULL ||
	    fprintf(db_file, "\n  my state %s at %s",
		    (state->me.state == startup) ?
		    dhcp_failover_state_name_print(state->saved_state) :
		    dhcp_failover_state_name_print(state->me.state),
		    tval) < 0)
		++errors;

	tval = print_time(state->partner.stos);
	if (tval == NULL ||
	    fprintf(db_file, "\n  partner state %s at %s",
		    dhcp_failover_state_name_print(state->partner.state),
		    tval) < 0)
		++errors;

	if (state -> i_am == secondary) {
		errno = 0;
		fprintf (db_file, "\n  mclt %ld;",
			 (unsigned long)state -> mclt);
		if (errno)
			++errors;
	}

        errno = 0;
	fprintf (db_file, "\n}\n");
	if (errno)
		++errors;

	if (errors) {
		log_info ("write_failover_state: unable to write state %s",
			  state -> name);
		lease_file_is_corrupt = 1;
		return 0;
	}

	return 1;

}
