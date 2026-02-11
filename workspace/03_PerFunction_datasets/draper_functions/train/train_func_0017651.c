file_cache_init(struct file_cache *cache, const char *pathname, int flags, mode_t mode)
{
	int ret;
	int fd;

	if (cache == NULL)
	{
		return -EINVAL;
	}

	fd = open(pathname, flags, mode);
	if (fd < 0)
	{
		return fd;
	}

	if (cache->cache_blocks == 0)
	{
		cache->cache_blocks = DEFAULT_CACHE_BLOCKS;
	}

	if (cache->block_size == 0)
	{
		cache->block_size = DEFAULT_BLOCK_SIZE;
	}

	ret = ffile_cache_init(cache, cache->cache_blocks * cache->block_size, cache->cache_blocks * cache->block_size);
	if (ret < 0)
	{
		goto out_close_fd;
	}

	cache->fd = fd;
	cache->start_block = 0;
	cache->read_pointer = cache->write_pointer = cache->start_block;
	text_copy(cache->pathname, pathname);

	return 0;

out_close_fd:
	close(fd);

	return ret;
}
