decode_recallslot_args(struct svc_rqst *rqstp,
					struct xdr_stream *xdr,
					struct cb_recallslotargs *args)
{
	__be32 *p;

	p = read_buf(xdr, 4);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_BADXDR);
	args->crsa_target_highest_slotid = ntohl(*p++);
	return 0;
}
