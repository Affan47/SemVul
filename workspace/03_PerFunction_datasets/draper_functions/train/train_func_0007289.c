ceph_readpage_from_fscache(struct inode *inode, struct page *page)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int ret;

	if (!cache_valid(ci))
		return -ENOBUFS;

	ret = fscache_read_or_alloc_page(ci->fscache, page,
					 ceph_readpage_from_fscache_complete, NULL,
					 GFP_KERNEL);

	switch (ret) {
		case 0:
			dout("page read submitted\n");
			return 0;
		case -ENOBUFS:
		case -ENODATA:
			dout("page/inode not in cache\n");
			return ret;
		default:
			dout("%s: unknown error ret = %i\n", __func__, ret);
			return ret;
	}
}
