tcm_loop_alloc_core_bus(void)
{
	int ret;

	tcm_loop_primary = root_device_register("tcm_loop_0");
	if (IS_ERR(tcm_loop_primary)) {
		pr_err("Unable to allocate tcm_loop_primary\n");
		return PTR_ERR(tcm_loop_primary);
	}

	ret = bus_register(&tcm_loop_lld_bus);
	if (ret) {
		pr_err("bus_register() failed for tcm_loop_lld_bus\n");
		goto dev_unreg;
	}

	ret = driver_register(&tcm_loop_driverfs);
	if (ret) {
		pr_err("driver_register() failed for"
				"tcm_loop_driverfs\n");
		goto bus_unreg;
	}

	pr_debug("Initialized TCM Loop Core Bus\n");
	return ret;

bus_unreg:
	bus_unregister(&tcm_loop_lld_bus);
dev_unreg:
	root_device_unregister(tcm_loop_primary);
	return ret;
}
