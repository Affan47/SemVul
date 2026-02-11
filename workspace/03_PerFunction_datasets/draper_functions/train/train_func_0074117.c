parse_rlimits( char *rlimits_str, int propagate_flag )
{
	slurm_rlimits_info_t *rli;
	char		     *tp;
	bool		     found;
	bool		     propagate_none = false;
	char		     *rlimits_str_dup;

	xassert( rlimits_str );

	if (strcmp(rlimits_str, "NONE") == 0) {
		propagate_none = true;
		propagate_flag = !propagate_flag;
	}

	if (propagate_none || strcmp( rlimits_str, "ALL" ) == 0) {


		for (rli = rlimits_info; rli->name; rli++)
			rli->propagate_flag = propagate_flag;
		rlimits_were_parsed = TRUE;
		return( 0 );
	}


	if (rlimits_were_parsed)
		for (rli = rlimits_info; rli->name; rli++)
			rli->propagate_flag = -1;

	rlimits_str_dup = xstrdup( rlimits_str );
	if ((tp = strtok( rlimits_str_dup, RLIMIT_DELIMS )) != NULL) {
		do {
			found = FALSE;
			for (rli = rlimits_info; rli->name; rli++) {


				if (strncmp( tp, RLIMIT_, LEN_RLIMIT_ ) == 0)
					tp += LEN_RLIMIT_;
				if (strcmp( tp, rli->name ))
					continue;
				rli->propagate_flag = propagate_flag;
				found = TRUE;
				break;
			}
			if (found == FALSE) {
				error( "Bad rlimit name: %s", tp );
				xfree( rlimits_str_dup );
				return( -1 );
			}
		} while ((tp = strtok( NULL, RLIMIT_DELIMS )));
	}
	xfree( rlimits_str_dup );


	for (rli = rlimits_info; rli->name; rli++)
		if (rli->propagate_flag == -1)
			rli->propagate_flag = ( ! propagate_flag );

	rlimits_were_parsed = TRUE;
	return( 0 );
}
