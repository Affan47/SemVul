memory_read_seek(struct archive *a, void *client_data, int64_t offset, int whence)
{
	struct read_memory_data *mine = (struct read_memory_data *)client_data;

	(void)a;
	switch (whence) {
	case SEEK_SET:
		mine->p = mine->start + offset;
		break;
	case SEEK_CUR:
		mine->p += offset;
		break;
	case SEEK_END:
		mine->p = mine->end + offset;
		break;
	default:
		return ARCHIVE_FATAL;
	}
	if (mine->p < mine->start) {
		mine->p = mine->start;
		return ARCHIVE_FAILED;
	}
	if (mine->p > mine->end) {
		mine->p = mine->end;
		return ARCHIVE_FAILED;
	}
	return (mine->p - mine->start);
}
