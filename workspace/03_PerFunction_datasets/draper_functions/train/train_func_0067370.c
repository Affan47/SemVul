conn_counter_destroy( void *key, void *data )
{
	slap_counters_t **prev, *sc;

	ldap_pvt_thread_mutex_lock( &slap_counters.sc_mutex );
	for ( prev = &slap_counters.sc_next, sc = slap_counters.sc_next; sc;
		prev = &sc->sc_next, sc = sc->sc_next ) {
		if ( sc == data ) {
			int i;

			*prev = sc->sc_next;

			ldap_pvt_mp_add( slap_counters.sc_bytes, sc->sc_bytes );
			ldap_pvt_mp_add( slap_counters.sc_pdu, sc->sc_pdu );
			ldap_pvt_mp_add( slap_counters.sc_entries, sc->sc_entries );
			ldap_pvt_mp_add( slap_counters.sc_refs, sc->sc_refs );
			ldap_pvt_mp_add( slap_counters.sc_ops_initiated, sc->sc_ops_initiated );
			ldap_pvt_mp_add( slap_counters.sc_ops_completed, sc->sc_ops_completed );
#ifdef SLAPD_MONITOR
			for ( i = 0; i < SLAP_OP_LAST; i++ ) {
				ldap_pvt_mp_add( slap_counters.sc_ops_initiated_[ i ], sc->sc_ops_initiated_[ i ] );
				ldap_pvt_mp_add( slap_counters.sc_ops_initiated_[ i ], sc->sc_ops_completed_[ i ] );
			}
#endif
			slap_counters_destroy( sc );
			ber_memfree_x( data, NULL );
			break;
		}
	}
	ldap_pvt_thread_mutex_unlock( &slap_counters.sc_mutex );
}
