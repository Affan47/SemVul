pc_cfadd( Operation *op, SlapReply *rs, Entry *p, ConfigArgs *ca )
{
	CfEntryInfo *pe = p->e_private;
	slap_overinst *on = (slap_overinst *)pe->ce_bi;
	cache_manager *cm = on->on_bi.bi_private;
	struct berval bv;


	bv.bv_len = snprintf( ca->cr_msg, sizeof( ca->cr_msg ),
		"olcDatabase=" SLAP_X_ORDERED_FMT "%s",
		0, cm->db.bd_info->bi_type );
	if ( bv.bv_len >= sizeof( ca->cr_msg ) ) {
		return -1;
	}
	bv.bv_val = ca->cr_msg;
	ca->be = &cm->db;
	cm->defer_db_open = 0;


	if ( cm->db.bd_info->bi_cf_ocs )
		config_build_entry( op, rs, pe, ca, &bv, cm->db.bd_info->bi_cf_ocs,
			&pcocs[1] );

	return 0;
}
