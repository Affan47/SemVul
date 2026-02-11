egg_buffer_get_string (EggBuffer *buffer, size_t offset, size_t *next_offset,
                       char **str_ret, EggBufferAllocator allocator)
{
	uint32_t len;

	if (!allocator)
		allocator = buffer->allocator;
	if (!allocator)
		allocator = DEFAULT_ALLOCATOR;

	if (!egg_buffer_get_uint32 (buffer, offset, &offset, &len)) {
		return 0;
	}
	if (len == 0xffffffff) {
		*next_offset = offset;
		*str_ret = NULL;
		return 1;
	} else if (len >= 0x7fffffff) {
		return 0;
	}

	if (buffer->len < len ||
	    offset > buffer->len - len) {
		return 0;
	}


	if (memchr (buffer->buf + offset, 0, len) != NULL)
		return 0;


	*str_ret = (allocator) (NULL, len + 1);
	if (!*str_ret)
		return 0;
	memcpy (*str_ret, buffer->buf + offset, len);


	(*str_ret)[len] = 0;
	*next_offset = offset + len;

	return 1;
}
