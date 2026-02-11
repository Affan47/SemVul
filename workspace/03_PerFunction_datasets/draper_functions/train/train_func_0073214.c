rtl92de_module_init(void)
{
	int ret = 0;

	spin_lock_init(&globalmutex_power);
	spin_lock_init(&globalmutex_for_fwdownload);
	spin_lock_init(&globalmutex_for_power_and_efuse);

	ret = pci_register_driver(&rtl92de_driver);
	if (ret)
		RT_ASSERT(false, "No device found\n");
	return ret;
}
