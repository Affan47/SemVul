ext2fs_get_generic_bitmap_range(ext2fs_generic_bitmap bmap,
					  errcode_t magic,
					  __u32 start, __u32 num,
					  void *out)
{
	if (!bmap || (bmap->magic != magic))
		return magic;

	if ((start < bmap->start) || (start+num-1 > bmap->real_end))
		return EXT2_ET_INVALID_ARGUMENT;

	memcpy(out, bmap->bitmap + (start >> 3), (num+7) >> 3);
	return 0;
}
