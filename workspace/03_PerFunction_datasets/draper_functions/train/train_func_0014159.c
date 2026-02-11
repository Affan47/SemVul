seqmod_db_close(
	BackendDB *be,
	ConfigReply *cr
)
{
	slap_overinst	*on = (slap_overinst *)be->bd_info;
	seqmod_info	*sm = (seqmod_info *)on->on_bi.bi_private;

	if ( sm ) {
		ldap_pvt_thread_mutex_destroy( &sm->sm_mutex );

		ch_free( sm );
	}

	return 0;
}
