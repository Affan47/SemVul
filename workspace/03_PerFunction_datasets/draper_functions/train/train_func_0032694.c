tbuf_write(const struct file_object *fo, filesize_t offset)
{
	size_t size = TBUF_WRITTEN_LEN();
	ssize_t ret;

	g_assert(fo);
	g_assert(size > 0);
	g_assert(size <= tbuf.size);

	ret = file_object_pwrite(fo, tbuf.arena, size, offset);
	if ((ssize_t) -1 == ret || (size_t) ret != size) {
		const char *error;

		error = (ssize_t) -1 == ret ? g_strerror(errno) : "Unknown error";
		g_warning("error while flushing trailer info for \"%s\": %s",
			file_object_get_pathname(fo), error);
	}
}
