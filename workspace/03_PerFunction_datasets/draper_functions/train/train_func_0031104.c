deviceenabled_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	unsigned int id;

	if (kstrtouint(buf, 10, &id))
		return -EINVAL;

	parahotplug_request_complete(id, 1);
	return count;
}
