remove_config(struct usb_composite_dev *cdev,
			      struct usb_configuration *config)
{
	while (!list_empty(&config->functions)) {
		struct usb_function		*f;

		f = list_first_entry(&config->functions,
				struct usb_function, list);
		list_del(&f->list);
		if (f->unbind) {
			DBG(cdev, "unbind function '%s'/%p\n", f->name, f);
			f->unbind(config, f);

		}
	}
	list_del(&config->list);
	if (config->unbind) {
		DBG(cdev, "unbind config '%s'/%p\n", config->label, config);
		config->unbind(config);

	}
}
