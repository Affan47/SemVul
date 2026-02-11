bma150_register_polled_device(struct bma150_data *bma150)
{
	struct input_polled_dev *ipoll_dev;
	int error;

	ipoll_dev = input_allocate_polled_device();
	if (!ipoll_dev)
		return -ENOMEM;

	ipoll_dev->private = bma150;
	ipoll_dev->open = bma150_poll_open;
	ipoll_dev->close = bma150_poll_close;
	ipoll_dev->poll = bma150_poll;
	ipoll_dev->poll_interval = BMA150_POLL_INTERVAL;
	ipoll_dev->poll_interval_min = BMA150_POLL_MIN;
	ipoll_dev->poll_interval_max = BMA150_POLL_MAX;

	bma150_init_input_device(bma150, ipoll_dev->input);

	error = input_register_polled_device(ipoll_dev);
	if (error) {
		input_free_polled_device(ipoll_dev);
		return error;
	}

	bma150->input_polled = ipoll_dev;
	bma150->input = ipoll_dev->input;

	return 0;
}
