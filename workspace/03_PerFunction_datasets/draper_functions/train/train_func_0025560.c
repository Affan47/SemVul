ldap_chain_db_init_one(
	BackendDB	*be )
{
	slap_overinst	*on = (slap_overinst *)be->bd_info;
	ldap_chain_t	*lc = (ldap_chain_t *)on->on_bi.bi_private;

	BackendInfo	*bi = be->bd_info;
	ldapinfo_t	*li;

	slap_op_t	t;

	be->bd_info = lback;
	be->be_private = NULL;
	t = lback->bi_db_init( be, NULL );
	if ( t != 0 ) {
		return t;
	}
	li = (ldapinfo_t *)be->be_private;
	li->li_urllist_f = NULL;
	li->li_urllist_p = NULL;


	li->li_nretries = lc->lc_common_li->li_nretries;
	li->li_flags = lc->lc_common_li->li_flags;
	li->li_version = lc->lc_common_li->li_version;
	for ( t = 0; t < SLAP_OP_LAST; t++ ) {
		li->li_timeout[ t ] = lc->lc_common_li->li_timeout[ t ];
	}
	be->bd_info = bi;

	return 0;
}
