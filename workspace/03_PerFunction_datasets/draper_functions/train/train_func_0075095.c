nfs4_xdr_dec_cb_layout(struct rpc_rqst *rqstp,
				  struct xdr_stream *xdr,
				  struct nfsd4_callback *cb)
{
	struct nfs4_cb_compound_hdr hdr;
	int status;

	status = decode_cb_compound4res(xdr, &hdr);
	if (unlikely(status))
		return status;

	if (cb) {
		status = decode_cb_sequence4res(xdr, cb);
		if (unlikely(status || cb->cb_seq_status))
			return status;
	}
	return decode_cb_op_status(xdr, OP_CB_LAYOUTRECALL, &cb->cb_status);
}
