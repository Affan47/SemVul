usb_udc_init(void)
{
	udc_class = class_create(THIS_MODULE, "udc");
	if (IS_ERR(udc_class)) {
		pr_err("failed to create udc class --> %ld\n",
				PTR_ERR(udc_class));
		return PTR_ERR(udc_class);
	}

	udc_class->dev_uevent = usb_udc_uevent;
	return 0;
}
