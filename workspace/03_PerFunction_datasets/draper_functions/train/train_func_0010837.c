io_channel_alloc_buf(io_channel io, int count, void *ptr)
{
	size_t	size;

	if (count == 0)
		size = io->block_size;
	else if (count > 0)
		size = io->block_size * count;
	else
		size = -count;

	if (io->align)
		return ext2fs_get_memalign(size, io->align, ptr);
	else
		return ext2fs_get_mem(size, ptr);
}
