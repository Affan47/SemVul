enclosure_add_device(struct enclosure_device *edev, int component,
			 struct device *dev)
{
	struct enclosure_component *cdev;
	int err;

	if (!edev || component >= edev->components)
		return -EINVAL;

	cdev = &edev->component[component];

	if (cdev->dev == dev)
		return -EEXIST;

	if (cdev->dev) {
		enclosure_remove_links(cdev);
		put_device(cdev->dev);
	}
	cdev->dev = get_device(dev);
	err = enclosure_add_links(cdev);
	if (err) {
		put_device(cdev->dev);
		cdev->dev = NULL;
	}
	return err;
}
