kernel_add_sysfs_param(const char *name,
					  const struct kernel_param *kparam,
					  unsigned int name_skip)
{
	struct module_kobject *mk;
	int err;

	mk = locate_module_kobject(name);
	if (!mk)
		return;


	if (mk->mp)
		sysfs_remove_group(&mk->kobj, &mk->mp->grp);


	err = add_sysfs_param(mk, kparam, kparam->name + name_skip);
	BUG_ON(err);
	err = sysfs_create_group(&mk->kobj, &mk->mp->grp);
	BUG_ON(err);
	kobject_uevent(&mk->kobj, KOBJ_ADD);
	kobject_put(&mk->kobj);
}
