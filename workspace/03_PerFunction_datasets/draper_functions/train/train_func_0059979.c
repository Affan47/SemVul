lzss_check(struct buffer *buffer)
{
	if (buffer != NULL && 4 <= buffer->size &&
	    (buffer->data[0] == '\x10' || buffer->data[0] == '\x11')) {
		u32 uncompressed_size = *(u32 *)buffer->data >> 8;

		if (buffer->size - 4 < uncompressed_size) {
			return true;
		}
	}
	return false;
}
