store_gcov_u32(void *buffer, size_t off, u32 v)
{
	u32 *data;

	if (buffer) {
		data = buffer + off;
		*data = v;
	}

	return sizeof(*data);
}
