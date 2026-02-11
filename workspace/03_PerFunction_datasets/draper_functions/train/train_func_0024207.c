w1_slave_release(struct device *dev)
{
	struct w1_slave *sl = dev_to_w1_slave(dev);

	dev_dbg(dev, "%s: Releasing %s [%p]\n", __func__, sl->name, sl);

	w1_family_put(sl->family);
	sl->master->slave_count--;
}
