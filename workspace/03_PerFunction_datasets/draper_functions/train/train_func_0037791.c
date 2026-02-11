xillybus_cleanup_chrdev(struct xilly_endpoint *endpoint)
{
	int minor;

	for (minor = endpoint->lowest_minor;
	     minor < (endpoint->lowest_minor + endpoint->num_channels);
	     minor++)
		device_destroy(xillybus_class, MKDEV(endpoint->major, minor));
	cdev_del(&endpoint->cdev);
	unregister_chrdev_region(MKDEV(endpoint->major,
				       endpoint->lowest_minor),
				 endpoint->num_channels);

	dev_info(endpoint->dev, "Removed %d device files.\n",
		 endpoint->num_channels);
}
