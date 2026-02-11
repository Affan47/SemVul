uinput_allocate_device(struct uinput_device *udev)
{
	udev->dev = input_allocate_device();
	if (!udev->dev)
		return -ENOMEM;

	udev->dev->event = uinput_dev_event;
	input_set_drvdata(udev->dev, udev);

	return 0;
}
