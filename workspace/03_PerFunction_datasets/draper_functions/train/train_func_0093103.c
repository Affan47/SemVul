decode_write3resok(struct xdr_stream *xdr,
			      struct nfs_pgio_res *result)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	result->count = be32_to_cpup(p++);
	result->verf->committed = be32_to_cpup(p++);
	if (unlikely(result->verf->committed > NFS_FILE_SYNC))
		goto out_badvalue;
	if (decode_writeverf3(xdr, &result->verf->verifier))
		goto out_eio;
	return result->count;
out_badvalue:
	dprintk("NFS: bad stable_how value: %u\n", result->verf->committed);
	return -EIO;
out_overflow:
	print_overflow_msg(__func__, xdr);
out_eio:
	return -EIO;
}
