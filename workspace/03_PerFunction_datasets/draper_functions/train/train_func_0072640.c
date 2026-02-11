vxfs_init(void)
{
	int rv;

	vxfs_inode_cachep = kmem_cache_create("vxfs_inode",
			sizeof(struct vxfs_inode_info), 0,
			SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD, NULL);
	if (!vxfs_inode_cachep)
		return -ENOMEM;
	rv = register_filesystem(&vxfs_fs_type);
	if (rv < 0)
		kmem_cache_destroy(vxfs_inode_cachep);
	return rv;
}
