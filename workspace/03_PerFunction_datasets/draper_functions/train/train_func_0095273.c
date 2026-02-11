encode_attr_change(struct xdr_stream *xdr, const uint32_t *bitmap, uint64_t change)
{
	__be32 *p;

	if (!(bitmap[0] & FATTR4_WORD0_CHANGE))
		return 0;
	p = xdr_reserve_space(xdr, 8);
	if (unlikely(!p))
		return htonl(NFS4ERR_RESOURCE);
	p = xdr_encode_hyper(p, change);
	return 0;
}
