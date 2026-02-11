agp_amd64_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct agp_bridge_data *bridge;
	u8 cap_ptr;
	int err;


	if (agp_bridges_found)
		return -ENODEV;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptr)
		return -ENODEV;


	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_8151_0) {
		amd8151_init(pdev, bridge);
	} else {
		dev_info(&pdev->dev, "AGP bridge [%04x/%04x]\n",
			 pdev->vendor, pdev->device);
	}

	bridge->driver = &amd_8151_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;


	pci_read_config_dword(pdev, bridge->capndx+PCI_AGP_STATUS, &bridge->mode);

	if (cache_nbs(pdev, cap_ptr) == -1) {
		agp_put_bridge(bridge);
		return -ENODEV;
	}

	if (pdev->vendor == PCI_VENDOR_ID_NVIDIA) {
		int ret = nforce3_agp_init(pdev);
		if (ret) {
			agp_put_bridge(bridge);
			return ret;
		}
	}

	if (pdev->vendor == PCI_VENDOR_ID_AL) {
		int ret = uli_agp_init(pdev);
		if (ret) {
			agp_put_bridge(bridge);
			return ret;
		}
	}

	pci_set_drvdata(pdev, bridge);
	err = agp_add_bridge(bridge);
	if (err < 0)
		return err;

	agp_bridges_found++;
	return 0;
}
