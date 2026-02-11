afs_readpages(struct file *file, struct address_space *mapping,
			 struct list_head *pages, unsigned nr_pages)
{
	struct key *key = file->private_data;
	struct afs_vnode *vnode;
	int ret = 0;

	_enter("{%d},{%lu},,%d",
	       key_serial(key), mapping->host->i_ino, nr_pages);

	ASSERT(key != NULL);

	vnode = AFS_FS_I(mapping->host);
	if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		_leave(" = -ESTALE");
		return -ESTALE;
	}


#ifdef CONFIG_AFS_FSCACHE
	ret = fscache_read_or_alloc_pages(vnode->cache,
					  mapping,
					  pages,
					  &nr_pages,
					  afs_file_readpage_read_complete,
					  NULL,
					  mapping_gfp_mask(mapping));
#else
	ret = -ENOBUFS;
#endif

	switch (ret) {

	case 0:
		BUG_ON(!list_empty(pages));
		BUG_ON(nr_pages != 0);
		_leave(" = 0 [reading all]");
		return 0;


	case -ENODATA:
	case -ENOBUFS:
		break;


	default:
		_leave(" = %d", ret);
		return ret;
	}


	ret = read_cache_pages(mapping, pages, afs_page_filler, key);

	_leave(" = %d [netting]", ret);
	return ret;
}
