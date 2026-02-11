io_flush_buffer(io_Writer* writer)
{
	if(writer->fp == NULL)
	{
		fprintf(stderr, "IO: (flush) no file pointer associated with writer (mem only ?)\n");
		fprintf(stderr, "IO: (flush) try to increase buffer size\n");
		return -1;
	}

	size_t nitems = 0;
	if (writer->buf_ptr > writer->buffer)
	{
		nitems= writer->buf_ptr - writer->buffer;
		if(fwrite(writer->buffer, 1, nitems, writer->fp) < nitems)
		{
			perror("IO: file write error");
			return -1;
		}
	}
	else if (writer->buf_ptr < writer->buffer)
	{
		fprintf(stderr, "IO: Bad buffer pointer - dropping buffer\n");
		writer->buf_ptr = writer->buffer;
		return -1;
	}

	int64_t size_inc = nitems - (writer->size - writer->position);
	if(size_inc > 0)
		writer->size += size_inc;

	writer->position = io_tell(writer);

	writer->buf_ptr = writer->buffer;


	if(writer->position > writer->size)
	{
		fprintf(stderr, "IO: file pointer ( %" PRIu64 " ) above expected file size ( %" PRIu64 " )\n", writer->position, writer->size);
		writer->size = writer->position;
	}

	return writer->position;
}
