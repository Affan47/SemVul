module_add_driver(struct module *mod, struct device_driver *drv)
{
	char *driver_name;
	int no_warn;
	struct module_kobject *mk = NULL;

	if (!drv)
		return;

	if (mod)
		mk = &mod->mkobj;
	else if (drv->mod_name) {
		struct kobject *mkobj;


		mkobj = kset_find_obj(module_kset, drv->mod_name);
		if (mkobj) {
			mk = container_of(mkobj, struct module_kobject, kobj);

			drv->p->mkobj = mk;

			kobject_put(mkobj);
		}
	}

	if (!mk)
		return;


	no_warn = sysfs_create_link(&drv->p->kobj, &mk->kobj, "module");
	driver_name = make_driver_name(drv);
	if (driver_name) {
		module_create_drivers_dir(mk);
		no_warn = sysfs_create_link(mk->drivers_dir, &drv->p->kobj,
					    driver_name);
		kfree(driver_name);
	}
}
