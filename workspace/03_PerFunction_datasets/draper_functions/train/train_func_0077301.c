qlcnic_pci_sriov_configure(struct pci_dev *dev, int num_vfs)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(dev);
	int err;

	if (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EBUSY;

	if (num_vfs == 0)
		err = qlcnic_pci_sriov_disable(adapter);
	else
		err = qlcnic_pci_sriov_enable(adapter, num_vfs);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return err;
}
