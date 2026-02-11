esre_attr_show(struct kobject *kobj,
			      struct attribute *_attr, char *buf)
{
	struct esre_entry *entry = to_entry(kobj);
	struct esre_attribute *attr = to_attr(_attr);


	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	return attr->show(entry, buf);
}
