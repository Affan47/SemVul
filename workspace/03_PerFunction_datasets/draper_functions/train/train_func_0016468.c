intel_iommu_init(void)
{
	int ret = -ENODEV;
	struct dmar_drhd_unit *drhd;
	struct intel_iommu *iommu;


	force_on = tboot_force_iommu();

	if (iommu_init_mempool()) {
		if (force_on)
			panic("tboot: Failed to initialize iommu memory\n");
		return -ENOMEM;
	}

	down_write(&dmar_global_lock);
	if (dmar_table_init()) {
		if (force_on)
			panic("tboot: Failed to initialize DMAR table\n");
		goto out_free_dmar;
	}

	if (dmar_dev_scope_init() < 0) {
		if (force_on)
			panic("tboot: Failed to initialize DMAR device scope\n");
		goto out_free_dmar;
	}

	if (no_iommu || dmar_disabled)
		goto out_free_dmar;

	if (list_empty(&dmar_rmrr_units))
		pr_info("No RMRR found\n");

	if (list_empty(&dmar_atsr_units))
		pr_info("No ATSR found\n");

	if (dmar_init_reserved_ranges()) {
		if (force_on)
			panic("tboot: Failed to reserve iommu ranges\n");
		goto out_free_reserved_range;
	}

	init_no_remapping_devices();

	ret = init_dmars();
	if (ret) {
		if (force_on)
			panic("tboot: Failed to initialize DMARs\n");
		pr_err("Initialization failed\n");
		goto out_free_reserved_range;
	}
	up_write(&dmar_global_lock);
	pr_info("Intel(R) Virtualization Technology for Directed I/O\n");

	init_timer(&unmap_timer);
#ifdef CONFIG_SWIOTLB
	swiotlb = 0;
#endif
	dma_ops = &intel_dma_ops;

	init_iommu_pm_ops();

	for_each_active_iommu(iommu, drhd)
		iommu->iommu_dev = iommu_device_create(NULL, iommu,
						       intel_iommu_groups,
						       "%s", iommu->name);

	bus_set_iommu(&pci_bus_type, &intel_iommu_ops);
	bus_register_notifier(&pci_bus_type, &device_nb);
	if (si_domain && !hw_pass_through)
		register_memory_notifier(&intel_iommu_memory_nb);

	intel_iommu_enabled = 1;

	return 0;

out_free_reserved_range:
	put_iova_domain(&reserved_iova_list);
out_free_dmar:
	intel_iommu_free_dmars();
	up_write(&dmar_global_lock);
	iommu_exit_mempool();
	return ret;
}
