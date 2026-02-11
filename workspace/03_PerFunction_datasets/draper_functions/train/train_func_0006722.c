collect_initialize() {
	int code;

	collect.on_bi.bi_type = "collect";
	collect.on_bi.bi_db_destroy = collect_destroy;
	collect.on_bi.bi_op_modify = collect_modify;
	collect.on_response = collect_response;

	collect.on_bi.bi_cf_ocs = collectocs;
	code = config_register_schema( collectcfg, collectocs );
	if ( code ) return code;

	return overlay_register( &collect );
}
