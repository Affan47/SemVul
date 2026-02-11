unix_write_byte(io_channel channel, unsigned long offset,
				 int size, const void *buf)
{
	struct unix_private_data *data;
	errcode_t	retval = 0;
	ssize_t		actual;

	EXT2_CHECK_MAGIC(channel, EXT2_ET_MAGIC_IO_CHANNEL);
	data = (struct unix_private_data *) channel->private_data;
	EXT2_CHECK_MAGIC(data, EXT2_ET_MAGIC_UNIX_IO_CHANNEL);

	if (channel->align != 0) {
#ifdef ALIGN_DEBUG
		printf("unix_write_byte: O_DIRECT fallback\n");
#endif
		return EXT2_ET_UNIMPLEMENTED;
	}

#ifndef NO_IO_CACHE


	if ((retval = flush_cached_blocks(channel, data, 1)))
		return retval;
#endif

	if (lseek(data->dev, offset + data->offset, SEEK_SET) < 0)
		return errno;

	actual = write(data->dev, buf, size);
	if (actual != size)
		return EXT2_ET_SHORT_WRITE;

	return 0;
}
