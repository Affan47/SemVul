vt596_probe(struct pci_dev *pdev,
		       const struct pci_device_id *id)
{
	unsigned char temp;
	int error;


	if (force_addr) {
		vt596_smba = force_addr & 0xfff0;
		force = 0;
		goto found;
	}

	if ((pci_read_config_word(pdev, id->driver_data, &vt596_smba)) ||
	    !(vt596_smba & 0x0001)) {

		if (id->device == PCI_DEVICE_ID_VIA_82C596_3 &&
		    !pci_read_config_word(pdev, SMBBA2, &vt596_smba) &&
		    (vt596_smba & 0x0001)) {
			SMBHSTCFG = 0x84;
		} else {

			dev_err(&pdev->dev, "Cannot configure "
				"SMBus I/O Base address\n");
			return -ENODEV;
		}
	}

	vt596_smba &= 0xfff0;
	if (vt596_smba == 0) {
		dev_err(&pdev->dev, "SMBus base address "
			"uninitialized - upgrade BIOS or use "
			"force_addr=0xaddr\n");
		return -ENODEV;
	}

found:
	error = acpi_check_region(vt596_smba, 8, vt596_driver.name);
	if (error)
		return -ENODEV;

	if (!request_region(vt596_smba, 8, vt596_driver.name)) {
		dev_err(&pdev->dev, "SMBus region 0x%x already in use!\n",
			vt596_smba);
		return -ENODEV;
	}

	pci_read_config_byte(pdev, SMBHSTCFG, &temp);


	if (force_addr) {
		pci_write_config_byte(pdev, SMBHSTCFG, temp & 0xfe);
		pci_write_config_word(pdev, id->driver_data, vt596_smba);
		pci_write_config_byte(pdev, SMBHSTCFG, temp | 0x01);
		dev_warn(&pdev->dev, "WARNING: SMBus interface set to new "
			 "address 0x%04x!\n", vt596_smba);
	} else if (!(temp & 0x01)) {
		if (force) {


			pci_write_config_byte(pdev, SMBHSTCFG, temp | 0x01);
			dev_info(&pdev->dev, "Enabling SMBus device\n");
		} else {
			dev_err(&pdev->dev, "SMBUS: Error: Host SMBus "
				"controller not enabled! - upgrade BIOS or "
				"use force=1\n");
			error = -ENODEV;
			goto release_region;
		}
	}

	dev_dbg(&pdev->dev, "VT596_smba = 0x%X\n", vt596_smba);

	switch (pdev->device) {
	case PCI_DEVICE_ID_VIA_CX700:
	case PCI_DEVICE_ID_VIA_VX800:
	case PCI_DEVICE_ID_VIA_VX855:
	case PCI_DEVICE_ID_VIA_VX900:
	case PCI_DEVICE_ID_VIA_8251:
	case PCI_DEVICE_ID_VIA_8237:
	case PCI_DEVICE_ID_VIA_8237A:
	case PCI_DEVICE_ID_VIA_8237S:
	case PCI_DEVICE_ID_VIA_8235:
	case PCI_DEVICE_ID_VIA_8233A:
	case PCI_DEVICE_ID_VIA_8233_0:
		vt596_features |= FEATURE_I2CBLOCK;
		break;
	case PCI_DEVICE_ID_VIA_82C686_4:


		if (pdev->revision >= 0x40)
			vt596_features |= FEATURE_I2CBLOCK;
		break;
	}

	vt596_adapter.dev.parent = &pdev->dev;
	snprintf(vt596_adapter.name, sizeof(vt596_adapter.name),
		 "SMBus Via Pro adapter at %04x", vt596_smba);

	vt596_pdev = pci_dev_get(pdev);
	error = i2c_add_adapter(&vt596_adapter);
	if (error) {
		pci_dev_put(vt596_pdev);
		vt596_pdev = NULL;
		goto release_region;
	}


	return -ENODEV;

release_region:
	release_region(vt596_smba, 8);
	return error;
}
