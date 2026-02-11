w1_master_attribute_show_slaves(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct w1_master *md = dev_to_w1_master(dev);
	int c = PAGE_SIZE;
	struct list_head *ent, *n;
	struct w1_slave *sl = NULL;

	mutex_lock(&md->list_mutex);

	list_for_each_safe(ent, n, &md->slist) {
		sl = list_entry(ent, struct w1_slave, w1_slave_entry);

		c -= snprintf(buf + PAGE_SIZE - c, c, "%s\n", sl->name);
	}
	if (!sl)
		c -= snprintf(buf + PAGE_SIZE - c, c, "not found.\n");

	mutex_unlock(&md->list_mutex);

	return PAGE_SIZE - c;
}
