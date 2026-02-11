Convert(const void* in_data, size_t in_size,
			void* out_data, size_t out_size,
			size_t* size_read, size_t* size_written)
    {
	size_t csize = (in_size < out_size) ? in_size : out_size;

	memcpy(out_data, in_data, csize);

	if (size_read)
	    *size_read = csize;
	if (size_written)
	    *size_written = csize;

	return 0;
    }
