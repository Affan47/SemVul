pnfs_do_write(struct nfs_pageio_descriptor *desc,
	      struct nfs_pgio_header *hdr, int how)
{
	const struct rpc_call_ops *call_ops = desc->pg_rpc_callops;
	struct pnfs_layout_segment *lseg = desc->pg_lseg;
	enum pnfs_try_status trypnfs;

	trypnfs = pnfs_try_to_write_data(hdr, call_ops, lseg, how);
	if (trypnfs == PNFS_NOT_ATTEMPTED)
		pnfs_write_through_mds(desc, hdr);
}
