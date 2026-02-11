encode_op_hdr(struct xdr_stream *xdr, uint32_t op, __be32 res)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 8);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE_HDR);
	*p++ = htonl(op);
	*p = res;
	return 0;
}
