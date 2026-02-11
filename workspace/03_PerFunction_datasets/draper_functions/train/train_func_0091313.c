buffer_append(buffer * restrict buf, const void * restrict input, size_t size)
{
	const unsigned char *in = input;
	size_t n, n_todo;

	debug("Writing %zu bytes to buffer (address: %p)", size, (void *)buf);

	for (n_todo = size; n_todo > 0; n_todo -= n, in += n) {
		size_t available = buf->last == NULL ?
		    0 : BUFFER_BLOCK_SIZE - buf->end_offset;

		if (available == 0) {
			block_add(buf);
			buf->end_offset = 0;
			available = BUFFER_BLOCK_SIZE;
		}
		n = MIN(n_todo, available);
		(void)memcpy(buf->last->data + buf->end_offset, in, n);
		buf->end_offset += n;
	}
	buf->size += size;
}
