decode_fsstat3resok(struct xdr_stream *xdr,
			       struct nfs_fsstat *result)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 8 * 6 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	p = xdr_decode_size3(p, &result->tbytes);
	p = xdr_decode_size3(p, &result->fbytes);
	p = xdr_decode_size3(p, &result->abytes);
	p = xdr_decode_size3(p, &result->tfiles);
	p = xdr_decode_size3(p, &result->ffiles);
	xdr_decode_size3(p, &result->afiles);

	return 0;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}
