sysfs_create_files(struct kobject *kobj, const struct attribute **ptr)
{
	int err = 0;
	int i;

	for (i = 0; ptr[i] && !err; i++)
		err = sysfs_create_file(kobj, ptr[i]);
	if (err)
		while (--i >= 0)
			sysfs_remove_file(kobj, ptr[i]);
	return err;
}
