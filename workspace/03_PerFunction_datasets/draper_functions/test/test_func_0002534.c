pccard_store_insert(struct device *dev, struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct pcmcia_socket *s = to_socket(dev);

	if (!count)
		return -EINVAL;

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_INSERT);

	return count;
}
