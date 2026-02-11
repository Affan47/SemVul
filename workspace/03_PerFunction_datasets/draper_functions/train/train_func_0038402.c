ufx_free(struct kref *kref)
{
	struct ufx_data *dev = container_of(kref, struct ufx_data, kref);


	if (dev->urbs.count > 0)
		ufx_free_urb_list(dev);

	pr_debug("freeing ufx_data %p", dev);

	kfree(dev);
}
