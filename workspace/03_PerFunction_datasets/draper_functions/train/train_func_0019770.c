filename_shrink(const char *filename, char *buf, size_t size)
{
	const char *ext;
	size_t ext_size = 0, ret;

	g_assert(filename);
	g_assert(buf);


	ext = strrchr(filename, '.');
	if (ext) {
		ext_size = strlen(ext) + 1;
		if (ext_size >= size) {


			ext_size = 0;
			ext = NULL;
		}
	}

	g_assert(ext_size < size);
	utf8_strlcpy(buf, filename, size - ext_size);


	if (ext) {
		g_strlcat(buf, ext, size);
	}

	ret = strlen(buf);
	g_assert(ret < size);
	return ret;
}
