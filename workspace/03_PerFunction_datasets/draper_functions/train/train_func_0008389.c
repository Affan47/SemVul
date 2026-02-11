nas_gpio_init(void)
{
	int i;
	int ret = 0;
	int nr_devices = 0;

	nr_devices = dmi_check_system(nas_led_whitelist);
	if (nodetect) {
		pr_info("skipping hardware autodetection\n");
		pr_info("Please send 'dmidecode' output to dave@sr71.net\n");
		nr_devices++;
	}

	if (nr_devices <= 0) {
		pr_info("no LED devices found\n");
		return -ENODEV;
	}

	pr_info("registering PCI driver\n");
	ret = pci_register_driver(&nas_gpio_pci_driver);
	if (ret)
		return ret;
	for (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++) {
		ret = register_nasgpio_led(i);
		if (ret)
			goto out_err;
	}


	set_power_light_amber_noblink();
	return 0;
out_err:
	for (i--; i >= 0; i--)
		unregister_nasgpio_led(i);
	pci_unregister_driver(&nas_gpio_pci_driver);
	return ret;
}
