rwm_callback_get( Operation *op )
{
	rwm_op_cb	*roc;

	roc = op->o_tmpalloc( sizeof( struct rwm_op_cb ), op->o_tmpmemctx );
	roc->cb.sc_cleanup = rwm_op_cleanup;
	roc->cb.sc_response = NULL;
	roc->cb.sc_next = op->o_callback;
	roc->cb.sc_private = &roc->ros;
	roc->ros.r_tag = op->o_tag;
	roc->ros.ro_dn = op->o_req_dn;
	roc->ros.ro_ndn = op->o_req_ndn;
	BER_BVZERO( &roc->ros.r_dn );
	BER_BVZERO( &roc->ros.r_ndn );
	BER_BVZERO( &roc->ros.rx_dn );
	BER_BVZERO( &roc->ros.rx_ndn );
	roc->ros.mapped_attrs = NULL;
	roc->ros.o_request = op->o_request;

	return roc;
}
