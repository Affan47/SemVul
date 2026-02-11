class_compat_register(const char *name)
{
	struct class_compat *cls;

	cls = kmalloc(sizeof(struct class_compat), GFP_KERNEL);
	if (!cls)
		return NULL;
	cls->kobj = kobject_create_and_add(name, &class_kset->kobj);
	if (!cls->kobj) {
		kfree(cls);
		return NULL;
	}
	return cls;
}
