nic_enable_msix(struct nicpf *nic)
{
	int i, ret;

	nic->num_vec = NIC_PF_MSIX_VECTORS;

	for (i = 0; i < nic->num_vec; i++)
		nic->msix_entries[i].entry = i;

	ret = pci_enable_msix(nic->pdev, nic->msix_entries, nic->num_vec);
	if (ret) {
		dev_err(&nic->pdev->dev,
			"Request for #%d msix vectors failed\n",
			   nic->num_vec);
		return ret;
	}

	nic->msix_enabled = 1;
	return 0;
}
