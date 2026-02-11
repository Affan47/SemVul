nfs_release_page(struct page *page, gfp_t gfp)
{
	struct address_space *mapping = page->mapping;

	dfprintk(PAGECACHE, "NFS: release_page(%p)\n", page);


	if (mapping) {
		struct nfs_server *nfss = NFS_SERVER(mapping->host);
		nfs_commit_inode(mapping->host, 0);
		if (gfpflags_allow_blocking(gfp) &&
		    !bdi_write_congested(&nfss->backing_dev_info)) {
			wait_on_page_bit_killable_timeout(page, PG_private,
							  HZ);
			if (PagePrivate(page))
				set_bdi_congested(&nfss->backing_dev_info,
						  BLK_RW_ASYNC);
		}
	}

	if (PagePrivate(page))
		return 0;
	return nfs_fscache_release_page(page, gfp);
}
