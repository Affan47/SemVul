glue_sub_search( Operation *op, SlapReply *rs, BackendDB *b0,
	slap_overinst *on )
{

	if ( op->o_bd == b0 && on->on_next ) {
		BackendInfo *bi = op->o_bd->bd_info;
		int rc = SLAP_CB_CONTINUE;
		for ( on=on->on_next; on; on=on->on_next ) {
			op->o_bd->bd_info = (BackendInfo *)on;
			if ( on->on_bi.bi_op_search ) {
				rc = on->on_bi.bi_op_search( op, rs );
				if ( rc != SLAP_CB_CONTINUE )
					break;
			}
		}
		op->o_bd->bd_info = bi;
		if ( rc != SLAP_CB_CONTINUE )
			return rc;
	}
	return op->o_bd->be_search( op, rs );
}
