create_icache(ext2_filsys fs)
{
	errcode_t	retval;

	if (fs->icache)
		return 0;
	retval = ext2fs_get_mem(sizeof(struct ext2_inode_cache), &fs->icache);
	if (retval)
		return retval;

	memset(fs->icache, 0, sizeof(struct ext2_inode_cache));
	retval = ext2fs_get_mem(fs->blocksize, &fs->icache->buffer);
	if (retval) {
		ext2fs_free_mem(&fs->icache);
		return retval;
	}
	fs->icache->buffer_blk = 0;
	fs->icache->cache_last = -1;
	fs->icache->cache_size = 4;
	fs->icache->refcount = 1;
	retval = ext2fs_get_array(fs->icache->cache_size,
				  sizeof(struct ext2_inode_cache_ent),
				  &fs->icache->cache);
	if (retval) {
		ext2fs_free_mem(&fs->icache->buffer);
		ext2fs_free_mem(&fs->icache);
		return retval;
	}
	ext2fs_flush_icache(fs);
	return 0;
}
