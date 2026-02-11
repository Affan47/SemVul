usb_get_timeout(void)
{
	struct timeval tv;
	int msec;
	int res;
	int pollrem;
	pollrem = dev_poll_remain_ms();
	res = libusb_get_next_timeout(NULL, &tv);
	if(res == 0)
		return pollrem;
	if(res < 0) {
		usbmuxd_log(LL_ERROR, "libusb_get_next_timeout failed: %d", res);
		return pollrem;
	}
	msec = tv.tv_sec * 1000;
	msec += tv.tv_usec / 1000;
	if(msec > pollrem)
		return pollrem;
	return msec;
}
