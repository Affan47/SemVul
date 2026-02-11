_accept_p(struct dev_filter *f, struct device *dev)
{
	struct dev_set *ds = (struct dev_set *) f->private;

	if (!ds->initialised)
		_init_devs(ds);


	if (ds->initialised != 1)
		return 1;

	if (!_set_lookup(ds, dev->dev)) {
		log_debug("%s: Skipping (sysfs)", dev_name(dev));
		return 0;
	} else
		return 1;
}
