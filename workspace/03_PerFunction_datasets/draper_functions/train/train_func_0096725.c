ext2fs_allocate_block_bitmap(ext2_filsys fs,
				       const char *descr,
				       ext2fs_block_bitmap *ret)
{
	__u64		start, end, real_end;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	fs->write_bitmaps = ext2fs_write_bitmaps;

	start = EXT2FS_B2C(fs, fs->super->s_first_data_block);
	end = EXT2FS_B2C(fs, ext2fs_blocks_count(fs->super)-1);
	real_end = ((__u64) EXT2_CLUSTERS_PER_GROUP(fs->super)
		    * (__u64) fs->group_desc_count)-1 + start;

	if (fs->flags & EXT2_FLAG_64BITS)
		return (ext2fs_alloc_generic_bmap(fs,
				EXT2_ET_MAGIC_BLOCK_BITMAP64,
				fs->default_bitmap_type,
				start, end, real_end, descr, ret));

	if ((end > ~0U) || (real_end > ~0U))
		return EXT2_ET_CANT_USE_LEGACY_BITMAPS;

	return (ext2fs_make_generic_bitmap(EXT2_ET_MAGIC_BLOCK_BITMAP, fs,
					   start, end, real_end,
					   descr, 0,
					   (ext2fs_generic_bitmap *) ret));
}
