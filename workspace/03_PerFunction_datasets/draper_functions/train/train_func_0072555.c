decode_uint64(struct xdr_stream *xdr, u64 *value)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 8);
	if (unlikely(p == NULL))
		goto out_overflow;
	xdr_decode_hyper(p, value);
	return 0;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}
