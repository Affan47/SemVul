mbfl_memory_device_strncat(mbfl_memory_device *device, const char *psrc, int len)
{
	unsigned char *w;

	if ((device->pos + len) >= device->length) {

		int newlen = device->length + len + MBFL_MEMORY_DEVICE_ALLOC_SIZE;
		unsigned char *tmp = (unsigned char *)mbfl_realloc((void *)device->buffer, newlen*sizeof(unsigned char));
		if (tmp == NULL) {
			return -1;
		}
		device->length = newlen;
		device->buffer = tmp;
	}

	w = &device->buffer[device->pos];
	device->pos += len;
	while (len > 0) {
		*w++ = *psrc++;
		len--;
	}

	return len;
}
