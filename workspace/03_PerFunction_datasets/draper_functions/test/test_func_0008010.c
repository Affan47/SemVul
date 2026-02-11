f2fs_destroy_extent_tree(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et = F2FS_I(inode)->extent_tree;
	unsigned int node_cnt = 0;

	if (!et)
		return;

	if (inode->i_nlink && !is_bad_inode(inode) && et->count) {
		atomic_dec(&et->refcount);
		return;
	}


	node_cnt = f2fs_destroy_extent_node(inode);


	down_write(&sbi->extent_tree_lock);
	atomic_dec(&et->refcount);
	f2fs_bug_on(sbi, atomic_read(&et->refcount) || et->count);
	radix_tree_delete(&sbi->extent_tree_root, inode->i_ino);
	kmem_cache_free(extent_tree_slab, et);
	sbi->total_ext_tree--;
	up_write(&sbi->extent_tree_lock);

	F2FS_I(inode)->extent_tree = NULL;

	trace_f2fs_destroy_extent_tree(inode, node_cnt);
}
