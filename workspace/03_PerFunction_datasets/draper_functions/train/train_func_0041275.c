glue_tool_sync (
	BackendDB *b0
)
{
	slap_overinst	*on = glue_tool_inst( b0->bd_info );
	glueinfo		*gi = on->on_bi.bi_private;
	BackendInfo		*bi = b0->bd_info;
	int i;


	for (i = 0; i<gi->gi_nodes; i++)
		if (gi->gi_n[i].gn_be->be_sync)
			gi->gi_n[i].gn_be->be_sync (gi->gi_n[i].gn_be);
	b0->bd_info = on->on_info->oi_orig;
	if ( b0->be_sync )
		b0->be_sync( b0 );
	b0->bd_info = bi;
	return 0;
}
