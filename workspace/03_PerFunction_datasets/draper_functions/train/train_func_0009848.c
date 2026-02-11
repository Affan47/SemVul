snd_output_buffer_need(snd_output_t *output, size_t size)
{
	snd_output_buffer_t *buffer = output->private_data;
	size_t _free = buffer->alloc - buffer->size;
	size_t alloc;
	unsigned char *buf;

	if (_free >= size)
		return _free;
	if (buffer->alloc == 0)
		alloc = 256;
	else
		alloc = buffer->alloc;
	while (alloc < buffer->size + size)
		alloc *= 2;
	buf = realloc(buffer->buf, alloc);
	if (!buf)
		return -ENOMEM;
	buffer->buf = buf;
	buffer->alloc = alloc;
	return buffer->alloc - buffer->size;
}
