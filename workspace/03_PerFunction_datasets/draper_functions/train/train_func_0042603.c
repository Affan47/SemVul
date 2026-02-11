nfs_page_search_commits_for_head_request_locked(struct nfs_inode *nfsi,
						struct page *page)
{
	struct nfs_page *freq, *t;
	struct nfs_commit_info cinfo;
	struct inode *inode = &nfsi->vfs_inode;

	nfs_init_cinfo_from_inode(&cinfo, inode);


	freq = pnfs_search_commit_reqs(inode, &cinfo, page);
	if (freq)
		return freq->wb_head;


	list_for_each_entry_safe(freq, t, &cinfo.mds->list, wb_list) {
		if (freq->wb_page == page)
			return freq->wb_head;
	}

	return NULL;
}
