buffer_get_utf8_string (Buffer *buffer,
                        gsize offset,
                        gsize *next_offset,
                        char **str_ret)
{
	gsize len;
	char *str;

	if (!buffer_get_string (buffer, offset, &offset, &str,
	                        (BufferAllocator)g_realloc))
		return FALSE;
	len = str ? strlen (str) : 0;

	if (str != NULL) {
		if (!g_utf8_validate (str, len, NULL)) {
			g_free (str);
			return FALSE;
		}
	}

	if (next_offset != NULL) {
		*next_offset = offset;
	}
	if (str_ret != NULL) {
		*str_ret = str;
	} else {
		g_free (str);
	}
	return TRUE;
}
