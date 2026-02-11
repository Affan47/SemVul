class_pktcdvd_store_remove(struct class *c,
					  struct class_attribute *attr,
					  const char *buf,
					size_t count)
{
	unsigned int major, minor;
	if (sscanf(buf, "%u:%u", &major, &minor) == 2) {
		pkt_remove_dev(MKDEV(major, minor));
		return count;
	}
	return -EINVAL;
}
