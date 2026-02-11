jffs2_create_slab_caches(void)
{
	full_dnode_slab = kmem_cache_create("jffs2_full_dnode",
					    sizeof(struct jffs2_full_dnode),
					    0, 0, NULL);
	if (!full_dnode_slab)
		goto err;

	raw_dirent_slab = kmem_cache_create("jffs2_raw_dirent",
					    sizeof(struct jffs2_raw_dirent),
					    0, SLAB_HWCACHE_ALIGN, NULL);
	if (!raw_dirent_slab)
		goto err;

	raw_inode_slab = kmem_cache_create("jffs2_raw_inode",
					   sizeof(struct jffs2_raw_inode),
					   0, SLAB_HWCACHE_ALIGN, NULL);
	if (!raw_inode_slab)
		goto err;

	tmp_dnode_info_slab = kmem_cache_create("jffs2_tmp_dnode",
						sizeof(struct jffs2_tmp_dnode_info),
						0, 0, NULL);
	if (!tmp_dnode_info_slab)
		goto err;

	raw_node_ref_slab = kmem_cache_create("jffs2_refblock",
					      sizeof(struct jffs2_raw_node_ref) * (REFS_PER_BLOCK + 1),
					      0, 0, NULL);
	if (!raw_node_ref_slab)
		goto err;

	node_frag_slab = kmem_cache_create("jffs2_node_frag",
					   sizeof(struct jffs2_node_frag),
					   0, 0, NULL);
	if (!node_frag_slab)
		goto err;

	inode_cache_slab = kmem_cache_create("jffs2_inode_cache",
					     sizeof(struct jffs2_inode_cache),
					     0, 0, NULL);
	if (!inode_cache_slab)
		goto err;

#ifdef CONFIG_JFFS2_FS_XATTR
	xattr_datum_cache = kmem_cache_create("jffs2_xattr_datum",
					     sizeof(struct jffs2_xattr_datum),
					     0, 0, NULL);
	if (!xattr_datum_cache)
		goto err;

	xattr_ref_cache = kmem_cache_create("jffs2_xattr_ref",
					   sizeof(struct jffs2_xattr_ref),
					   0, 0, NULL);
	if (!xattr_ref_cache)
		goto err;
#endif

	return 0;
 err:
	jffs2_destroy_slab_caches();
	return -ENOMEM;
}
