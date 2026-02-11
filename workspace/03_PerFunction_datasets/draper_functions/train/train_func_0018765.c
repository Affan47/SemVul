sssvlv_initialize()
{
	int rc;

	sssvlv.on_bi.bi_type				= "sssvlv";
	sssvlv.on_bi.bi_db_init				= sssvlv_db_init;
	sssvlv.on_bi.bi_db_destroy			= sssvlv_db_destroy;
	sssvlv.on_bi.bi_db_open				= sssvlv_db_open;
	sssvlv.on_bi.bi_connection_destroy	= sssvlv_connection_destroy;
	sssvlv.on_bi.bi_op_search			= sssvlv_op_search;

	sssvlv.on_bi.bi_cf_ocs = sssvlv_ocs;

	rc = config_register_schema( sssvlv_cfg, sssvlv_ocs );
	if ( rc )
		return rc;

	rc = overlay_register( &sssvlv );
	if ( rc != LDAP_SUCCESS ) {
		Debug( LDAP_DEBUG_ANY, "Failed to register server side sort overlay\n", 0, 0, 0 );
	}

	return rc;
}
