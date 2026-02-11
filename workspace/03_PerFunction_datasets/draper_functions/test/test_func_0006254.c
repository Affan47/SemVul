amd_iommu_v2_exit(void)
{
	struct device_state *dev_state;
	int i;

	if (!amd_iommu_v2_supported())
		return;

	amd_iommu_unregister_ppr_notifier(&ppr_nb);

	flush_workqueue(iommu_wq);


	for (i = 0; i < MAX_DEVICES; ++i) {
		dev_state = get_device_state(i);

		if (dev_state == NULL)
			continue;

		WARN_ON_ONCE(1);

		put_device_state(dev_state);
		amd_iommu_free_device(dev_state->pdev);
	}

	destroy_workqueue(iommu_wq);
}
