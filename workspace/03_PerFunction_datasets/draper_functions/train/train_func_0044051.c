egg_buffer_get_uint32 (EggBuffer *buffer, size_t offset, size_t *next_offset,
                                 uint32_t *val)
{
	unsigned char *ptr;
	if (buffer->len < 4 || offset > buffer->len - 4) {
		buffer->failures++;
		return 0;
	}
	ptr = (unsigned char*)buffer->buf + offset;
	if (val != NULL)
		*val = egg_buffer_decode_uint32 (ptr);
	if (next_offset != NULL)
		*next_offset = offset + 4;
	return 1;
}
