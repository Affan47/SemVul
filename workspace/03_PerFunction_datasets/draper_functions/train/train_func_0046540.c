inc_wptr(unsigned int *wptr, unsigned int increment_bytes,
				unsigned int buffer_size_bytes)
{
	unsigned int temp = *wptr + increment_bytes / sizeof(uint32_t);

	BUG_ON((temp * sizeof(uint32_t)) > buffer_size_bytes);
	*wptr = temp;
}
