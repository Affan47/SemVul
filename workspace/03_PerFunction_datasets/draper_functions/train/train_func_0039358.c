pnfs_osd_xdr_ioerr_reserve_space(struct xdr_stream *xdr)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 32 + 24);
	if (unlikely(!p))
		dprintk("%s: out of xdr space\n", __func__);

	return p;
}
