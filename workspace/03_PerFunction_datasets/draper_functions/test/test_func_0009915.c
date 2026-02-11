genwqe_pci_fundamental_reset(struct pci_dev *pci_dev)
{
	int rc;


	pci_cfg_access_lock(pci_dev);
	pci_save_state(pci_dev);
	rc = pci_set_pcie_reset_state(pci_dev, pcie_warm_reset);
	if (!rc) {

		msleep(250);
		pci_set_pcie_reset_state(pci_dev, pcie_deassert_reset);

		msleep(2000);
	}
	pci_restore_state(pci_dev);
	pci_cfg_access_unlock(pci_dev);
	return rc;
}
