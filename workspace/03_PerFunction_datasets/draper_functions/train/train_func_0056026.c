extent_create_backing_file(struct block_allocation *alloc,
	u64 backing_len, const char *filename)
{
	off64_t offset = 0;
	for (; alloc != NULL && backing_len > 0; get_next_region(alloc)) {
		u32 region_block;
		u32 region_len;
		u32 len;
		get_region(alloc, &region_block, &region_len);

		len = min(region_len * info.block_size, backing_len);

		sparse_file_add_file(info.sparse_file, filename, offset, len,
				region_block);
		offset += len;
		backing_len -= len;
	}
}
