buffer_helper_growthsize(t_buffer *buffer, size_t newsize)
{
	if (newsize >= buffer->class->maxsize) {
		return buffer->class->maxsize;
	}
	if (newsize < buffer->msize) {
		return buffer->msize;
	}
	return (size_t)(newsize * 1.5);
}
