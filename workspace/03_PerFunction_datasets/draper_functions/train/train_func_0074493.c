ext2fs_test_block_bitmap_range2(ext2fs_block_bitmap bmap,
				    blk64_t block, unsigned int num)
{
	__u64	end = block + num;

	if (!bmap)
		return EINVAL;

	if (num == 1)
		return !ext2fs_test_generic_bmap((ext2fs_generic_bitmap)
						 bmap, block);

	if (EXT2FS_IS_32_BITMAP(bmap)) {
		if ((block+num-1) & ~0xffffffffULL) {
			ext2fs_warn_bitmap2((ext2fs_generic_bitmap) bmap,
					    EXT2FS_UNMARK_ERROR, 0xffffffff);
			return EINVAL;
		}
		return ext2fs_test_block_bitmap_range(
			(ext2fs_generic_bitmap) bmap, block, num);
	}

	if (!EXT2FS_IS_64_BITMAP(bmap))
		return EINVAL;

	INC_STAT(bmap, test_ext_count);


	block >>= bmap->cluster_bits;
	end += (1 << bmap->cluster_bits) - 1;
	end >>= bmap->cluster_bits;
	num = end - block;

	if ((block < bmap->start) || (block+num-1 > bmap->end)) {
		ext2fs_warn_bitmap(EXT2_ET_BAD_BLOCK_TEST, block,
				   bmap->description);
		return EINVAL;
	}

	return bmap->bitmap_ops->test_clear_bmap_extent(bmap, block, num);
}
