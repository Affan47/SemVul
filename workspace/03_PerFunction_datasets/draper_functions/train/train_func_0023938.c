visorbus_exit(void)
{
	struct list_head *listentry, *listtmp;

	visorchipset_register_busdev(NULL, NULL, NULL);
	remove_all_visor_devices();

	flush_workqueue(periodic_dev_workqueue);
	destroy_workqueue(periodic_dev_workqueue);
	periodic_dev_workqueue = NULL;

	if (periodic_test_workqueue) {
		cancel_delayed_work(&periodic_work);
		flush_workqueue(periodic_test_workqueue);
		destroy_workqueue(periodic_test_workqueue);
		periodic_test_workqueue = NULL;
	}

	list_for_each_safe(listentry, listtmp, &list_all_bus_instances) {
		struct visor_device *dev = list_entry(listentry,
						      struct visor_device,
						      list_all);
		remove_bus_instance(dev);
	}
	remove_bus_type();
}
