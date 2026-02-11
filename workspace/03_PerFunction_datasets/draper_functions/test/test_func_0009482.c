mbfl_wchar_device_init(mbfl_wchar_device *device)
{
	if (device) {
		device->buffer = (unsigned int *)0;
		device->length = 0;
		device->pos= 0;
		device->allocsz = MBFL_MEMORY_DEVICE_ALLOC_SIZE;
	}
}
