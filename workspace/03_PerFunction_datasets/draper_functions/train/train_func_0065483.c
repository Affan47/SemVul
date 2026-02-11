applesmc_key_at_index_store(struct device *dev,
	struct device_attribute *attr, const char *sysfsbuf, size_t count)
{
	unsigned long newkey;

	if (kstrtoul(sysfsbuf, 10, &newkey) < 0
	    || newkey >= smcreg.key_count)
		return -EINVAL;

	key_at_index = newkey;
	return count;
}
