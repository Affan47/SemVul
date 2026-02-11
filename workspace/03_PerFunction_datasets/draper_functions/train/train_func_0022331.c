do_register_con_driver(const struct consw *csw, int first, int last)
{
	struct module *owner = csw->owner;
	struct con_driver *con_driver;
	const char *desc;
	int i, retval = 0;

	WARN_CONSOLE_UNLOCKED();

	if (!try_module_get(owner))
		return -ENODEV;

	for (i = 0; i < MAX_NR_CON_DRIVER; i++) {
		con_driver = &registered_con_driver[i];


		if (con_driver->con == csw)
			retval = -EBUSY;
	}

	if (retval)
		goto err;

	desc = csw->con_startup();
	if (!desc) {
		retval = -ENODEV;
		goto err;
	}

	retval = -EINVAL;

	for (i = 0; i < MAX_NR_CON_DRIVER; i++) {
		con_driver = &registered_con_driver[i];

		if (con_driver->con == NULL &&
		    !(con_driver->flag & CON_DRIVER_FLAG_ZOMBIE)) {
			con_driver->con = csw;
			con_driver->desc = desc;
			con_driver->node = i;
			con_driver->flag = CON_DRIVER_FLAG_MODULE |
			                   CON_DRIVER_FLAG_INIT;
			con_driver->first = first;
			con_driver->last = last;
			retval = 0;
			break;
		}
	}

	if (retval)
		goto err;

	con_driver->dev =
		device_create_with_groups(vtconsole_class, NULL,
					  MKDEV(0, con_driver->node),
					  con_driver, con_dev_groups,
					  "vtcon%i", con_driver->node);
	if (IS_ERR(con_driver->dev)) {
		printk(KERN_WARNING "Unable to create device for %s; "
		       "errno = %ld\n", con_driver->desc,
		       PTR_ERR(con_driver->dev));
		con_driver->dev = NULL;
	} else {
		vtconsole_init_device(con_driver);
	}

err:
	module_put(owner);
	return retval;
}
