syncprov_qresp( opcookie *opc, syncops *so, int mode )
{
	syncres *sr;
	int srsize;
	struct berval cookie = opc->sctxcsn;

	if ( mode == LDAP_SYNC_NEW_COOKIE ) {
		syncprov_info_t	*si = opc->son->on_bi.bi_private;

		slap_compose_sync_cookie( NULL, &cookie, si->si_ctxcsn,
			so->s_rid, slap_serverID ? slap_serverID : -1);
	}

	srsize = sizeof(syncres) + opc->suuid.bv_len + 1 +
		opc->sdn.bv_len + 1 + opc->sndn.bv_len + 1;
	if ( cookie.bv_len )
		srsize += cookie.bv_len + 1;
	sr = ch_malloc( srsize );
	sr->s_next = NULL;
	sr->s_e = opc->se;

	if ( opc->se )
		inc_mutexint( opc->se->e_private );
	sr->s_dn.bv_val = (char *)(sr + 1);
	sr->s_dn.bv_len = opc->sdn.bv_len;
	sr->s_mode = mode;
	sr->s_isreference = opc->sreference;
	sr->s_ndn.bv_val = lutil_strcopy( sr->s_dn.bv_val,
		 opc->sdn.bv_val ) + 1;
	sr->s_ndn.bv_len = opc->sndn.bv_len;
	sr->s_uuid.bv_val = lutil_strcopy( sr->s_ndn.bv_val,
		 opc->sndn.bv_val ) + 1;
	sr->s_uuid.bv_len = opc->suuid.bv_len;
	AC_MEMCPY( sr->s_uuid.bv_val, opc->suuid.bv_val, opc->suuid.bv_len );
	if ( cookie.bv_len ) {
		sr->s_csn.bv_val = sr->s_uuid.bv_val + sr->s_uuid.bv_len + 1;
		strcpy( sr->s_csn.bv_val, cookie.bv_val );
	} else {
		sr->s_csn.bv_val = NULL;
	}
	sr->s_csn.bv_len = cookie.bv_len;

	if ( mode == LDAP_SYNC_NEW_COOKIE && cookie.bv_val ) {
		ch_free( cookie.bv_val );
	}

	ldap_pvt_thread_mutex_lock( &so->s_mutex );
	if ( !so->s_res ) {
		so->s_res = sr;
	} else {
		so->s_restail->s_next = sr;
	}
	so->s_restail = sr;


	if ( so->s_flags & PS_WROTE_BASE ) {
		so->s_flags ^= PS_WROTE_BASE;
		so->s_flags |= PS_FIND_BASE;
	}
	if (( so->s_flags & (PS_IS_DETACHED|PS_TASK_QUEUED)) == PS_IS_DETACHED ) {
		syncprov_qstart( so );
	}
	ldap_pvt_thread_mutex_unlock( &so->s_mutex );
	return LDAP_SUCCESS;
}
