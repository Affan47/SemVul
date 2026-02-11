squashfs_put_super(struct super_block *sb)
{
	if (sb->s_fs_info) {
		struct squashfs_sb_info *sbi = sb->s_fs_info;
		squashfs_cache_delete(sbi->block_cache);
		squashfs_cache_delete(sbi->fragment_cache);
		squashfs_cache_delete(sbi->read_page);
		squashfs_decompressor_destroy(sbi);
		kfree(sbi->id_table);
		kfree(sbi->fragment_index);
		kfree(sbi->meta_index);
		kfree(sbi->inode_lookup_table);
		kfree(sbi->xattr_id_table);
		kfree(sb->s_fs_info);
		sb->s_fs_info = NULL;
	}
}
