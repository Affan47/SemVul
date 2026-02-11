usnic_uiom_detach_dev_from_pd(struct usnic_uiom_pd *pd, struct device *dev)
{
	struct usnic_uiom_dev *uiom_dev;
	int found = 0;

	spin_lock(&pd->lock);
	list_for_each_entry(uiom_dev, &pd->devs, link) {
		if (uiom_dev->dev == dev) {
			found = 1;
			break;
		}
	}

	if (!found) {
		usnic_err("Unable to free dev %s - not found\n",
				dev_name(dev));
		spin_unlock(&pd->lock);
		return;
	}

	list_del(&uiom_dev->link);
	pd->dev_cnt--;
	spin_unlock(&pd->lock);

	return iommu_detach_device(pd->domain, dev);
}
