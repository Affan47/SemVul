aem_exit(void)
{
	struct aem_data *p1, *next1;

	ipmi_smi_watcher_unregister(&driver_data.bmc_events);
	driver_unregister(&aem_driver.driver);
	list_for_each_entry_safe(p1, next1, &driver_data.aem_devices, list)
		aem_delete(p1);
}
