archive_compressor_bzip2_write(struct archive_write_filter *f,
    const void *buff, size_t length)
{
	struct private_data *data = (struct private_data *)f->data;


	data->total_in += length;


	SET_NEXT_IN(data, buff);
	data->stream.avail_in = length;
	if (drive_compressor(f, data, 0))
		return (ARCHIVE_FATAL);
	return (ARCHIVE_OK);
}
