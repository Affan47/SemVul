module_attr_store(struct kobject *kobj,
				struct attribute *attr,
				const char *buf, size_t len)
{
	struct module_attribute *attribute;
	struct module_kobject *mk;
	int ret;

	attribute = to_module_attr(attr);
	mk = to_module_kobject(kobj);

	if (!attribute->store)
		return -EIO;

	ret = attribute->store(attribute, mk, buf, len);

	return ret;
}
