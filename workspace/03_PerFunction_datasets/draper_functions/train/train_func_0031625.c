o2hb_region_block_bytes_store(struct config_item *item,
					     const char *page,
					     size_t count)
{
	struct o2hb_region *reg = to_o2hb_region(item);
	int status;
	unsigned long block_bytes;
	unsigned int block_bits;

	if (reg->hr_bdev)
		return -EINVAL;

	status = o2hb_read_block_input(reg, page, count,
				       &block_bytes, &block_bits);
	if (status)
		return status;

	reg->hr_block_bytes = (unsigned int)block_bytes;
	reg->hr_block_bits = block_bits;

	return count;
}
