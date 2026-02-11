getrec_thr(void *ctx)
{
	ldap_pvt_thread_mutex_lock( &add_mutex );
	while (!add_stop) {
		trec.rc = getrec0((Erec *)&trec);
		trec.ready = 1;
		while (trec.ready)
			ldap_pvt_thread_cond_wait( &add_cond, &add_mutex );

		if ( trec.rc == 0 || trec.rc == -1 )
			break;
	}
	ldap_pvt_thread_mutex_unlock( &add_mutex );
	return NULL;
}
