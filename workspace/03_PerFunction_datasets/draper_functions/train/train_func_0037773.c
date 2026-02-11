fet_poll(device_t dev_base)
{
	struct fet_device *dev = (struct fet_device *)dev_base;

	if (usleep(50000) < 0)
		return DEVICE_STATUS_INTR;

	if (xfer(dev, C_STATE, NULL, 0, 1, 0) < 0) {
		printc_err("fet: polling failed\n");
		return DEVICE_STATUS_ERROR;
	}

	if (!(dev->fet_reply.argv[0] & FET_POLL_RUNNING))
		return DEVICE_STATUS_HALTED;

	return DEVICE_STATUS_RUNNING;
}
