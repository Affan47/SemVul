be_roce_register_driver(struct ocrdma_driver *drv)
{
	struct be_adapter *dev;

	mutex_lock(&be_adapter_list_lock);
	if (ocrdma_drv) {
		mutex_unlock(&be_adapter_list_lock);
		return -EINVAL;
	}
	ocrdma_drv = drv;
	list_for_each_entry(dev, &be_adapter_list, entry) {
		struct net_device *netdev;

		_be_roce_dev_add(dev);
		netdev = dev->netdev;
	}
	mutex_unlock(&be_adapter_list_lock);
	return 0;
}
