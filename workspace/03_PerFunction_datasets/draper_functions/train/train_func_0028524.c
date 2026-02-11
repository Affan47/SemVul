aac_define_int_mode(struct aac_dev *dev)
{
	int i, msi_count, min_msix;

	msi_count = i = 0;

	if (dev->max_msix == 0 ||
	    dev->pdev->device == PMC_DEVICE_S6 ||
	    dev->sync_mode) {
		dev->max_msix = 1;
		dev->vector_cap =
			dev->scsi_host_ptr->can_queue +
			AAC_NUM_MGT_FIB;
		return;
	}


	msi_count = min(dev->max_msix,
		(unsigned int)num_online_cpus());

	dev->max_msix = msi_count;

	if (msi_count > AAC_MAX_MSIX)
		msi_count = AAC_MAX_MSIX;

	for (i = 0; i < msi_count; i++)
		dev->msixentry[i].entry = i;

	if (msi_count > 1 &&
	    pci_find_capability(dev->pdev, PCI_CAP_ID_MSIX)) {
		min_msix = 2;
		i = pci_enable_msix_range(dev->pdev,
				    dev->msixentry,
				    min_msix,
				    msi_count);
		if (i > 0) {
			dev->msi_enabled = 1;
			msi_count = i;
		} else {
			dev->msi_enabled = 0;
			printk(KERN_ERR "%s%d: MSIX not supported!! Will try MSI 0x%x.\n",
					dev->name, dev->id, i);
		}
	}

	if (!dev->msi_enabled) {
		msi_count = 1;
		i = pci_enable_msi(dev->pdev);

		if (!i) {
			dev->msi_enabled = 1;
			dev->msi = 1;
		} else {
			printk(KERN_ERR "%s%d: MSI not supported!! Will try INTx 0x%x.\n",
					dev->name, dev->id, i);
		}
	}

	if (!dev->msi_enabled)
		dev->max_msix = msi_count = 1;
	else {
		if (dev->max_msix > msi_count)
			dev->max_msix = msi_count;
	}
	dev->vector_cap =
		(dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB) /
		msi_count;
}
