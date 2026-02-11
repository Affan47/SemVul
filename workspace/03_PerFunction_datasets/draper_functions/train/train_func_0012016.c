_and_p(struct dev_filter *f, struct device *dev)
{
	struct dev_filter **filters = (struct dev_filter **) f->private;

	while (*filters) {
		if (!(*filters)->passes_filter(*filters, dev))
			return 0;
		filters++;
	}

	log_debug("Using %s", dev_name(dev));

	return 1;
}
