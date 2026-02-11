old_fashioned_read(struct text *text)
{
	char *raw;
	ssize_t got, total = 0;
	size_t max;
#define CHUNK 1024

	do {
		buffer_insert(text->buffer, NULL, total, CHUNK);
		max = buffer_raw(text->buffer, &raw, total, CHUNK);
		errno = 0;
		got = read(text->fd, raw, max);
		if (got < 0) {
			message("%s: can't read",
				path_format(text->path));
			buffer_delete(text->buffer, 0, total + CHUNK);
			return -1;
		}
		buffer_delete(text->buffer, total + got, CHUNK - got);
		total += got;
	} while (got);

	return total;
}
