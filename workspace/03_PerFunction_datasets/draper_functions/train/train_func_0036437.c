skd_pci_resume(struct pci_dev *pdev)
{
	int i;
	int rc = 0;
	struct skd_device *skdev;

	skdev = pci_get_drvdata(pdev);
	if (!skdev) {
		pr_err("%s: no device data for PCI\n", pci_name(pdev));
		return -1;
	}

	pci_set_power_state(pdev, PCI_D0);
	pci_enable_wake(pdev, PCI_D0, 0);
	pci_restore_state(pdev);

	rc = pci_enable_device(pdev);
	if (rc)
		return rc;
	rc = pci_request_regions(pdev, DRV_NAME);
	if (rc)
		goto err_out;
	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (!rc) {
		if (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64))) {

			pr_err("(%s): consistent DMA mask error %d\n",
			       pci_name(pdev), rc);
		}
	} else {
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (rc) {

			pr_err("(%s): DMA mask error %d\n",
			       pci_name(pdev), rc);
			goto err_out_regions;
		}
	}

	pci_set_master(pdev);
	rc = pci_enable_pcie_error_reporting(pdev);
	if (rc) {
		pr_err("(%s): bad enable of PCIe error reporting rc=%d\n",
		       skdev->name, rc);
		skdev->pcie_error_reporting_is_enabled = 0;
	} else
		skdev->pcie_error_reporting_is_enabled = 1;

	for (i = 0; i < SKD_MAX_BARS; i++) {

		skdev->mem_phys[i] = pci_resource_start(pdev, i);
		skdev->mem_size[i] = (u32)pci_resource_len(pdev, i);
		skdev->mem_map[i] = ioremap(skdev->mem_phys[i],
					    skdev->mem_size[i]);
		if (!skdev->mem_map[i]) {
			pr_err("(%s): Unable to map adapter memory!\n",
			       skd_name(skdev));
			rc = -ENODEV;
			goto err_out_iounmap;
		}
		pr_debug("%s:%s:%d mem_map=%p, phyd=%016llx, size=%d\n",
			 skdev->name, __func__, __LINE__,
			 skdev->mem_map[i],
			 (uint64_t)skdev->mem_phys[i], skdev->mem_size[i]);
	}
	rc = skd_acquire_irq(skdev);
	if (rc) {

		pr_err("(%s): interrupt resource error %d\n",
		       pci_name(pdev), rc);
		goto err_out_iounmap;
	}

	rc = skd_start_timer(skdev);
	if (rc)
		goto err_out_timer;

	init_waitqueue_head(&skdev->waitq);

	skd_start_device(skdev);

	return rc;

err_out_timer:
	skd_stop_device(skdev);
	skd_release_irq(skdev);

err_out_iounmap:
	for (i = 0; i < SKD_MAX_BARS; i++)
		if (skdev->mem_map[i])
			iounmap(skdev->mem_map[i]);

	if (skdev->pcie_error_reporting_is_enabled)
		pci_disable_pcie_error_reporting(pdev);

err_out_regions:
	pci_release_regions(pdev);

err_out:
	pci_disable_device(pdev);
	return rc;
}
