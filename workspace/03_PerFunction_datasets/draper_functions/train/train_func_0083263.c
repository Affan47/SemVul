early_amd_iommu_init(void)
{
	struct acpi_table_header *ivrs_base;
	acpi_size ivrs_size;
	acpi_status status;
	int i, ret = 0;

	if (!amd_iommu_detected)
		return -ENODEV;

	status = acpi_get_table_with_size("IVRS", 0, &ivrs_base, &ivrs_size);
	if (status == AE_NOT_FOUND)
		return -ENODEV;
	else if (ACPI_FAILURE(status)) {
		const char *err = acpi_format_exception(status);
		pr_err("AMD-Vi: IVRS table error: %s\n", err);
		return -EINVAL;
	}


	ret = find_last_devid_acpi(ivrs_base);
	if (ret)
		goto out;

	dev_table_size     = tbl_size(DEV_TABLE_ENTRY_SIZE);
	alias_table_size   = tbl_size(ALIAS_TABLE_ENTRY_SIZE);
	rlookup_table_size = tbl_size(RLOOKUP_TABLE_ENTRY_SIZE);


	ret = -ENOMEM;
	amd_iommu_dev_table = (void *)__get_free_pages(GFP_KERNEL | __GFP_ZERO,
				      get_order(dev_table_size));
	if (amd_iommu_dev_table == NULL)
		goto out;


	amd_iommu_alias_table = (void *)__get_free_pages(GFP_KERNEL,
			get_order(alias_table_size));
	if (amd_iommu_alias_table == NULL)
		goto out;


	amd_iommu_rlookup_table = (void *)__get_free_pages(
			GFP_KERNEL | __GFP_ZERO,
			get_order(rlookup_table_size));
	if (amd_iommu_rlookup_table == NULL)
		goto out;

	amd_iommu_pd_alloc_bitmap = (void *)__get_free_pages(
					    GFP_KERNEL | __GFP_ZERO,
					    get_order(MAX_DOMAIN_ID/8));
	if (amd_iommu_pd_alloc_bitmap == NULL)
		goto out;


	for (i = 0; i <= amd_iommu_last_bdf; ++i)
		amd_iommu_alias_table[i] = i;


	amd_iommu_pd_alloc_bitmap[0] = 1;

	spin_lock_init(&amd_iommu_pd_lock);


	ret = init_iommu_all(ivrs_base);
	if (ret)
		goto out;

	if (amd_iommu_irq_remap)
		amd_iommu_irq_remap = check_ioapic_information();

	if (amd_iommu_irq_remap) {


		ret = -ENOMEM;
		amd_iommu_irq_cache = kmem_cache_create("irq_remap_cache",
				MAX_IRQS_PER_TABLE * sizeof(u32),
				IRQ_TABLE_ALIGNMENT,
				0, NULL);
		if (!amd_iommu_irq_cache)
			goto out;

		irq_lookup_table = (void *)__get_free_pages(
				GFP_KERNEL | __GFP_ZERO,
				get_order(rlookup_table_size));
		if (!irq_lookup_table)
			goto out;
	}

	ret = init_memory_definitions(ivrs_base);
	if (ret)
		goto out;


	init_device_table();

out:

	early_acpi_os_unmap_memory((char __iomem *)ivrs_base, ivrs_size);
	ivrs_base = NULL;

	return ret;
}
