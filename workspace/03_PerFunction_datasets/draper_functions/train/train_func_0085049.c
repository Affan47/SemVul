genftbl()
	{
	register int i;
	int end_of_buffer_action = num_rules + 1;

	out_str_dec( long_align ? C_long_decl : C_short_decl,
		"yy_accept", lastdfa + 1 );

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	for ( i = 1; i <= lastdfa; ++i )
		{
		register int anum = dfaacc[i].dfaacc_state;

		mkdata( anum );

		if ( trace && anum )
			fprintf( stderr, _( "state # %d accepts: [%d]\n" ),
				i, anum );
		}

	dataend();

	if ( useecs )
		genecs();


	}
