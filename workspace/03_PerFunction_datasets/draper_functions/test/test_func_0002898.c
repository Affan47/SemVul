input_close_polled_device(struct input_dev *input)
{
	struct input_polled_dev *dev = input_get_drvdata(input);

	cancel_delayed_work_sync(&dev->work);

	if (dev->close)
		dev->close(dev);
}
