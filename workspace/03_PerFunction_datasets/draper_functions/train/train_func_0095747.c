ext2fs_find_first_zero_generic_bmap(ext2fs_generic_bitmap bitmap,
					      __u64 start, __u64 end, __u64 *out)
{
	__u64 cstart, cend, cout;
	errcode_t retval;

	if (!bitmap)
		return EINVAL;

	if (EXT2FS_IS_32_BITMAP(bitmap)) {
		blk_t blk = 0;

		if (((start) & ~0xffffffffULL) ||
		    ((end) & ~0xffffffffULL)) {
			ext2fs_warn_bitmap2(bitmap, EXT2FS_TEST_ERROR, start);
			return EINVAL;
		}

		retval = ext2fs_find_first_zero_generic_bitmap(bitmap, start,
							       end, &blk);
		if (retval == 0)
			*out = blk;
		return retval;
	}

	if (!EXT2FS_IS_64_BITMAP(bitmap))
		return EINVAL;

	cstart = start >> bitmap->cluster_bits;
	cend = end >> bitmap->cluster_bits;

	if (cstart < bitmap->start || cend > bitmap->end || start > end) {
		warn_bitmap(bitmap, EXT2FS_TEST_ERROR, start);
		return EINVAL;
	}

	if (bitmap->bitmap_ops->find_first_zero) {
		retval = bitmap->bitmap_ops->find_first_zero(bitmap, cstart,
							     cend, &cout);
		if (retval)
			return retval;
	found:
		cout <<= bitmap->cluster_bits;
		*out = (cout >= start) ? cout : start;
		return 0;
	}

	for (cout = cstart; cout <= cend; cout++)
		if (!bitmap->bitmap_ops->test_bmap(bitmap, cout))
			goto found;

	return ENOENT;
}
