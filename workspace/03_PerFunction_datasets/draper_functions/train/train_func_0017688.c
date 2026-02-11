next_entry_seek(struct archive_read *a, struct iso9660 *iso9660,
    struct file_info **pfile)
{
	struct file_info *file;
	int r;

	r = next_cache_entry(a, iso9660, pfile);
	if (r != ARCHIVE_OK)
		return (r);
	file = *pfile;


	if (file->size == 0)
		file->offset = iso9660->current_position;


	if (iso9660->entry_bytes_unconsumed) {
		__archive_read_consume(a, iso9660->entry_bytes_unconsumed);
		iso9660->entry_bytes_unconsumed = 0;
	}


	if (iso9660->current_position < file->offset) {
		int64_t step;

		step = file->offset - iso9660->current_position;
		step = __archive_read_consume(a, step);
		if (step < 0)
			return ((int)step);
		iso9660->current_position = file->offset;
	}


	return (ARCHIVE_OK);
}
