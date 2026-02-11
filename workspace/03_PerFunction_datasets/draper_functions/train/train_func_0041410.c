bl_pg_init_read(struct nfs_pageio_descriptor *pgio, struct nfs_page *req)
{
	if (!is_aligned_req(pgio, req, SECTOR_SIZE)) {
		nfs_pageio_reset_read_mds(pgio);
		return;
	}

	pnfs_generic_pg_init_read(pgio, req);
}
