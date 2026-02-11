pt_init(void)
{
	int unit;
	int err;

	if (disable) {
		err = -EINVAL;
		goto out;
	}

	if (pt_detect()) {
		err = -ENODEV;
		goto out;
	}

	err = register_chrdev(major, name, &pt_fops);
	if (err < 0) {
		printk("pt_init: unable to get major number %d\n", major);
		for (unit = 0; unit < PT_UNITS; unit++)
			if (pt[unit].present)
				pi_release(pt[unit].pi);
		goto out;
	}
	major = err;
	pt_class = class_create(THIS_MODULE, "pt");
	if (IS_ERR(pt_class)) {
		err = PTR_ERR(pt_class);
		goto out_chrdev;
	}

	for (unit = 0; unit < PT_UNITS; unit++)
		if (pt[unit].present) {
			device_create(pt_class, NULL, MKDEV(major, unit), NULL,
				      "pt%d", unit);
			device_create(pt_class, NULL, MKDEV(major, unit + 128),
				      NULL, "pt%dn", unit);
		}
	goto out;

out_chrdev:
	unregister_chrdev(major, "pt");
out:
	return err;
}
