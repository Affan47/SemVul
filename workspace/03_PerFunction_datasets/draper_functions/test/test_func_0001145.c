ext2fs_make_generic_bitmap(errcode_t magic, ext2_filsys fs,
				     __u32 start, __u32 end, __u32 real_end,
				     const char *descr, char *init_map,
				     ext2fs_generic_bitmap *ret)
{
	ext2fs_generic_bitmap	bitmap;
	errcode_t		retval;
	size_t			size;

	retval = ext2fs_get_mem(sizeof(struct ext2fs_struct_generic_bitmap),
				&bitmap);
	if (retval)
		return retval;

	bitmap->magic = magic;
	bitmap->fs = fs;
	bitmap->start = start;
	bitmap->end = end;
	bitmap->real_end = real_end;
	switch (magic) {
	case EXT2_ET_MAGIC_INODE_BITMAP:
		bitmap->base_error_code = EXT2_ET_BAD_INODE_MARK;
		break;
	case EXT2_ET_MAGIC_BLOCK_BITMAP:
		bitmap->base_error_code = EXT2_ET_BAD_BLOCK_MARK;
		break;
	default:
		bitmap->base_error_code = EXT2_ET_BAD_GENERIC_MARK;
	}
	if (descr) {
		retval = ext2fs_get_mem(strlen(descr)+1, &bitmap->description);
		if (retval) {
			ext2fs_free_mem(&bitmap);
			return retval;
		}
		strcpy(bitmap->description, descr);
	} else
		bitmap->description = 0;

	size = (size_t) (((bitmap->real_end - bitmap->start) / 8) + 1);

	size = (size + 7) & ~3;
	retval = ext2fs_get_mem(size, &bitmap->bitmap);
	if (retval) {
		ext2fs_free_mem(&bitmap->description);
		ext2fs_free_mem(&bitmap);
		return retval;
	}

	if (init_map)
		memcpy(bitmap->bitmap, init_map, size);
	else
		memset(bitmap->bitmap, 0, size);
	*ret = bitmap;
	return 0;
}
