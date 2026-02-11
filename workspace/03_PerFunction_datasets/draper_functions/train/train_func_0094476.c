evemu_create(const struct evemu_device *dev, int fd)
{
	struct uinput_user_dev udev;
	int ret, i;

	memset(&udev, 0, sizeof(udev));
	memcpy(udev.name, dev->name, sizeof(udev.name));
	udev.id = dev->id;
	for (i = 0; i < ABS_CNT; i++) {
		if (!evemu_has_event(dev, EV_ABS, i))
			continue;
		udev.absmax[i] = evemu_get_abs_maximum(dev, i);
		udev.absmin[i] = evemu_get_abs_minimum(dev, i);
		udev.absfuzz[i] = evemu_get_abs_fuzz(dev, i);
		udev.absflat[i] = evemu_get_abs_flat(dev, i);
	}

	ret = set_prop(dev, fd);
	if (ret < 0)
		return ret;

	for (i = 0; i < EV_CNT; i++) {
		ret = set_mask(dev, i, fd);
		if (ret < 0)
			return ret;
	}

	SYSCALL(ret = write(fd, &udev, sizeof(udev)));
	if (ret < 0)
		return ret;

	SYSCALL(ret = ioctl(fd, UI_DEV_CREATE, NULL));
	return ret;
}
