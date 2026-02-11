act2_write(libusb_device_handle* hudev, void* buff, size_t size)
{
	int actual_length, ret;
	ret = libusb_bulk_transfer(hudev, ACT2_EP_OUT, buff,
	                           size, &actual_length, ACT2_TIMEOUT);
	if (ret) {
		errno = proc_libusb_error(ret);
		return -1;
	}
	return actual_length;
}
