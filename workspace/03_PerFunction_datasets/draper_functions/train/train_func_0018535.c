chirp_reli_flush( struct chirp_file *file, time_t stoptime )
{
	INT64_T result;

	if(file->buffer_valid && file->buffer_dirty) {
		result = chirp_reli_pwrite_unbuffered(file,file->buffer,file->buffer_valid,file->buffer_offset,stoptime);
	} else {
		result = 0;
	}

	file->buffer_valid = 0;
	file->buffer_dirty = 0;
	file->buffer_offset = 0;

	return result;
}
