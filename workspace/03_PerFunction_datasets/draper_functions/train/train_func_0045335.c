config_tool_entry_first_x(
	BackendDB *be,
	struct berval *base,
	int scope,
	Filter *f )
{
	CfBackInfo *cfb = be->be_private;
	BackendInfo *bi = cfb->cb_db.bd_info;

	if ( bi && bi->bi_tool_entry_first_x ) {
		return bi->bi_tool_entry_first_x( &cfb->cb_db, base, scope, f );
	}
	return NOID;
}
