sock_over_response( Operation *op, SlapReply *rs )
{
	slap_overinst *on = (slap_overinst *)op->o_bd->bd_info;
	struct sockinfo *si = (struct sockinfo *)on->on_bi.bi_private;
	FILE *fp;

	if ( rs->sr_type == REP_RESULT ) {
		if ( !( si->si_resps & SOCK_REP_RESULT ))
			return SLAP_CB_CONTINUE;
	} else if ( rs->sr_type == REP_SEARCH ) {
		if ( !( si->si_resps & SOCK_REP_SEARCH ))
			return SLAP_CB_CONTINUE;
	} else
		return SLAP_CB_CONTINUE;

	if (( fp = opensock( si->si_sockpath )) == NULL )
		return SLAP_CB_CONTINUE;

	if ( rs->sr_type == REP_RESULT ) {

		fprintf( fp, "RESULT\n" );
		fprintf( fp, "msgid: %ld\n", (long) op->o_msgid );
		sock_print_conn( fp, op->o_conn, si );
		fprintf( fp, "code: %d\n", rs->sr_err );
		if ( rs->sr_matched )
			fprintf( fp, "matched: %s\n", rs->sr_matched );
		if (rs->sr_text )
			fprintf( fp, "info: %s\n", rs->sr_text );
	} else {

		int len;
		fprintf( fp, "ENTRY\n" );
		fprintf( fp, "msgid: %ld\n", (long) op->o_msgid );
		sock_print_conn( fp, op->o_conn, si );
		ldap_pvt_thread_mutex_lock( &entry2str_mutex );
		fprintf( fp, "%s", entry2str( rs->sr_entry, &len ) );
		ldap_pvt_thread_mutex_unlock( &entry2str_mutex );
	}
	fprintf( fp, "\n" );
	fclose( fp );

	return SLAP_CB_CONTINUE;
}
