syncprov_db_init(
	BackendDB *be,
	ConfigReply *cr
)
{
	slap_overinst	*on = (slap_overinst *)be->bd_info;
	syncprov_info_t	*si;

	if ( SLAP_ISGLOBALOVERLAY( be ) ) {
		Debug( LDAP_DEBUG_ANY,
			"syncprov must be instantiated within a database.\n",
			0, 0, 0 );
		return 1;
	}

	si = ch_calloc(1, sizeof(syncprov_info_t));
	on->on_bi.bi_private = si;
	ldap_pvt_thread_rdwr_init( &si->si_csn_rwlock );
	ldap_pvt_thread_mutex_init( &si->si_ops_mutex );
	ldap_pvt_thread_mutex_init( &si->si_mods_mutex );
	ldap_pvt_thread_mutex_init( &si->si_resp_mutex );

	csn_anlist[0].an_desc = slap_schema.si_ad_entryCSN;
	csn_anlist[0].an_name = slap_schema.si_ad_entryCSN->ad_cname;
	csn_anlist[1].an_desc = slap_schema.si_ad_entryUUID;
	csn_anlist[1].an_name = slap_schema.si_ad_entryUUID->ad_cname;

	uuid_anlist[0].an_desc = slap_schema.si_ad_entryUUID;
	uuid_anlist[0].an_name = slap_schema.si_ad_entryUUID->ad_cname;

	return 0;
}
