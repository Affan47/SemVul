iio_free_chan_devattr_list(struct list_head *attr_list)
{
	struct iio_dev_attr *p, *n;

	list_for_each_entry_safe(p, n, attr_list, l) {
		kfree(p->dev_attr.attr.name);
		list_del(&p->l);
		kfree(p);
	}
}
