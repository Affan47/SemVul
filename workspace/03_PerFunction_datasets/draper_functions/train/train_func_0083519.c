qlcnic_validate_subsystem_id(struct qlcnic_adapter *adapter,
					 int index)
{
	struct pci_dev *pdev = adapter->pdev;
	unsigned short subsystem_vendor;
	bool ret = true;

	subsystem_vendor = pdev->subsystem_vendor;

	if (pdev->device == PCI_DEVICE_ID_QLOGIC_QLE824X ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_QLE834X) {
		if (qlcnic_boards[index].sub_vendor == subsystem_vendor &&
		    qlcnic_boards[index].sub_device == pdev->subsystem_device)
			ret = true;
		else
			ret = false;
	}

	return ret;
}
