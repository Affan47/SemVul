dds_db_open(
	BackendDB	*be,
	ConfigReply	*cr )
{
	slap_overinst	*on = (slap_overinst *)be->bd_info;
	dds_info_t	*di = on->on_bi.bi_private;
	int		rc = 0;
	void		*thrctx = ldap_pvt_thread_pool_context();

	if ( slapMode & SLAP_TOOL_MODE )
		return 0;

	if ( DDS_OFF( di ) ) {
		goto done;
	}

	if ( SLAP_SINGLE_SHADOW( be ) ) {
		Log1( LDAP_DEBUG_ANY, LDAP_LEVEL_ERR,
			"DDS incompatible with shadow database \"%s\".\n",
			be->be_suffix[ 0 ].bv_val );
		return 1;
	}

	if ( di->di_max_ttl == 0 ) {
		di->di_max_ttl = DDS_RF2589_DEFAULT_TTL;
	}

	if ( di->di_min_ttl == 0 ) {
		di->di_max_ttl = DDS_RF2589_DEFAULT_TTL;
	}

	di->di_suffix = be->be_suffix;
	di->di_nsuffix = be->be_nsuffix;


	if ( di->di_max_dynamicObjects > 0 ) {

		be->bd_info = (BackendInfo *)on->on_info;
		rc = dds_expire( thrctx, di );
		be->bd_info = (BackendInfo *)on;
		if ( rc != LDAP_SUCCESS ) {
			rc = 1;
			goto done;
		}

		rc = dds_count( thrctx, be );
		if ( rc != LDAP_SUCCESS ) {
			rc = 1;
			goto done;
		}
	}


	ldap_pvt_thread_mutex_lock( &slapd_rq.rq_mutex );
	di->di_expire_task = ldap_pvt_runqueue_insert( &slapd_rq,
		DDS_INTERVAL( di ),
		dds_expire_fn, di, "dds_expire_fn",
		be->be_suffix[ 0 ].bv_val );
	ldap_pvt_thread_mutex_unlock( &slapd_rq.rq_mutex );


	rc = entry_info_register( dds_entry_info, (void *)di );

done:;

	return rc;
}
