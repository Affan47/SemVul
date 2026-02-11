nfs_end_page_writeback(struct nfs_page *req)
{
	struct inode *inode = page_file_mapping(req->wb_page)->host;
	struct nfs_server *nfss = NFS_SERVER(inode);

	if (!nfs_page_group_sync_on_bit(req, PG_WB_END))
		return;

	end_page_writeback(req->wb_page);
	if (atomic_long_dec_return(&nfss->writeback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(&nfss->backing_dev_info, BLK_RW_ASYNC);
}
