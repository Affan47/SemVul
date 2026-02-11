pnfs_generic_pg_init_write(struct nfs_pageio_descriptor *pgio,
			   struct nfs_page *req, u64 wb_size)
{
	if (pgio->pg_lseg == NULL)
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   req->wb_context,
						   req_offset(req),
						   wb_size,
						   IOMODE_RW,
						   GFP_NOFS);

	if (pgio->pg_lseg == NULL)
		nfs_pageio_reset_write_mds(pgio);
}
