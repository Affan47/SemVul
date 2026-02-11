memberof_initialize( void )
{
	int			code, i;

	for ( i = 0; as[ i ].desc != NULL; i++ ) {
		code = register_at( as[ i ].desc, as[ i ].adp, 0 );
		if ( code ) {
			Debug( LDAP_DEBUG_ANY,
				"memberof_initialize: register_at #%d failed\n",
				i, 0, 0 );
			return code;
		}
	}

	memberof.on_bi.bi_type = "memberof";

	memberof.on_bi.bi_db_init = memberof_db_init;
	memberof.on_bi.bi_db_open = memberof_db_open;
	memberof.on_bi.bi_db_destroy = memberof_db_destroy;

	memberof.on_bi.bi_op_add = memberof_op_add;
	memberof.on_bi.bi_op_delete = memberof_op_delete;
	memberof.on_bi.bi_op_modify = memberof_op_modify;
	memberof.on_bi.bi_op_modrdn = memberof_op_modrdn;

	memberof.on_bi.bi_cf_ocs = mo_ocs;

	code = config_register_schema( mo_cfg, mo_ocs );
	if ( code ) return code;

	return overlay_register( &memberof );
}
