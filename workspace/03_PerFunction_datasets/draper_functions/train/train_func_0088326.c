xennet_remove(struct xenbus_device *dev)
{
	struct netfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "%s\n", dev->nodename);

	xennet_disconnect_backend(info);

	unregister_netdev(info->netdev);

	if (info->queues)
		xennet_destroy_queues(info);
	xennet_free_netdev(info->netdev);

	return 0;
}
