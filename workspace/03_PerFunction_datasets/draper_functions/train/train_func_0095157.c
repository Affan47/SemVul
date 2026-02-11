pcie_portdrv_slot_reset(struct pci_dev *dev)
{
	pci_ers_result_t status = PCI_ERS_RESULT_RECOVERED;


	if (dev->error_state == pci_channel_io_frozen) {
		dev->state_saved = true;
		pci_restore_state(dev);
		pcie_portdrv_restore_config(dev);
		pci_enable_pcie_error_reporting(dev);
	}


	device_for_each_child(&dev->dev, &status, slot_reset_iter);
	return status;
}
