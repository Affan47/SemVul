igb_probe_vfs(struct igb_adapter *adapter)
{
#ifdef CONFIG_PCI_IOV
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_hw *hw = &adapter->hw;


	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211))
		return;


	igb_set_interrupt_capability(adapter, true);
	igb_reset_interrupt_capability(adapter);

	pci_sriov_set_totalvfs(pdev, 7);
	igb_enable_sriov(pdev, max_vfs);

#endif
}
