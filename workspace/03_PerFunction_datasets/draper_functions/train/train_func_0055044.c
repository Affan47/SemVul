ext2fs_copy_generic_bmap(ext2fs_generic_bitmap src,
				   ext2fs_generic_bitmap *dest)
{
	char *descr, *new_descr;
	ext2fs_generic_bitmap	new_bmap;
	errcode_t retval;

	if (!src)
		return EINVAL;

	if (EXT2FS_IS_32_BITMAP(src))
		return ext2fs_copy_generic_bitmap(src, dest);

	if (!EXT2FS_IS_64_BITMAP(src))
		return EINVAL;


	retval = ext2fs_get_memzero(sizeof(struct ext2fs_struct_generic_bitmap),
				    &new_bmap);
	if (retval)
		return retval;


#ifdef BMAP_STATS_OPS
	src->stats.copy_count++;
#endif
#ifdef BMAP_STATS
	if (gettimeofday(&new_bmap->stats.created,
			 (struct timezone *) NULL) == -1) {
		perror("gettimeofday");
		ext2fs_free_mem(&new_bmap);
		return 1;
	}
	new_bmap->stats.type = src->stats.type;
#endif


	new_bmap->magic = src->magic;
	new_bmap->fs = src->fs;
	new_bmap->start = src->start;
	new_bmap->end = src->end;
	new_bmap->real_end = src->real_end;
	new_bmap->bitmap_ops = src->bitmap_ops;
	new_bmap->base_error_code = src->base_error_code;
	new_bmap->cluster_bits = src->cluster_bits;

	descr = src->description;
	if (descr) {
		retval = ext2fs_get_mem(strlen(descr)+10, &new_descr);
		if (retval) {
			ext2fs_free_mem(&new_bmap);
			return retval;
		}
		sprintf(new_descr, "copy of %s", descr);
		new_bmap->description = new_descr;
	}

	retval = src->bitmap_ops->copy_bmap(src, new_bmap);
	if (retval) {
		ext2fs_free_mem(&new_bmap->description);
		ext2fs_free_mem(&new_bmap);
		return retval;
	}

	*dest = new_bmap;

	return 0;
}
