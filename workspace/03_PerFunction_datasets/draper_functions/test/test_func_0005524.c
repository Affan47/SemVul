edd_init(void)
{
	int i;
	int rc=0;
	struct edd_device *edev;

	printk(KERN_INFO "BIOS EDD facility v%s %s, %d devices found\n",
	       EDD_VERSION, EDD_DATE, edd_num_devices());

	if (!edd_num_devices()) {
		printk(KERN_INFO "EDD information not available.\n");
		return -ENODEV;
	}

	edd_kset = kset_create_and_add("edd", NULL, firmware_kobj);
	if (!edd_kset)
		return -ENOMEM;

	for (i = 0; i < edd_num_devices(); i++) {
		edev = kzalloc(sizeof (*edev), GFP_KERNEL);
		if (!edev) {
			rc = -ENOMEM;
			goto out;
		}

		rc = edd_device_register(edev, i);
		if (rc) {
			kfree(edev);
			goto out;
		}
		edd_devices[i] = edev;
	}

	return 0;

out:
	while (--i >= 0)
		edd_device_unregister(edd_devices[i]);
	kset_unregister(edd_kset);
	return rc;
}
