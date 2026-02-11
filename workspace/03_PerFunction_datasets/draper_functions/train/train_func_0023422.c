atl1e_reset_hw(struct atl1e_hw *hw)
{
	struct atl1e_adapter *adapter = hw->adapter;
	struct pci_device *pdev = adapter->pdev;
	int timeout = 0;
	u32 idle_status_data = 0;
	u16 pci_cfg_cmd_word = 0;


	pci_read_config_word(pdev, PCI_COMMAND, &pci_cfg_cmd_word);
	if ((pci_cfg_cmd_word & (PCI_COMMAND_IO | PCI_COMMAND_MEM |
				 PCI_COMMAND_MASTER))
			!= (PCI_COMMAND_IO | PCI_COMMAND_MEM |
			    PCI_COMMAND_MASTER)) {
		pci_cfg_cmd_word |= (PCI_COMMAND_IO | PCI_COMMAND_MEM |
				     PCI_COMMAND_MASTER);
		pci_write_config_word(pdev, PCI_COMMAND, pci_cfg_cmd_word);
	}


	AT_WRITE_REG(hw, REG_MASTER_CTRL,
			MASTER_CTRL_LED_MODE | MASTER_CTRL_SOFT_RST);
	wmb();
	mdelay(1);


	for (timeout = 0; timeout < AT_HW_MAX_IDLE_DELAY; timeout++) {
		idle_status_data = AT_READ_REG(hw, REG_IDLE_STATUS);
		if (idle_status_data == 0)
			break;
		mdelay(1);
	}

	if (timeout >= AT_HW_MAX_IDLE_DELAY) {
		DBG("atl1e: MAC reset timeout\n");
		return AT_ERR_TIMEOUT;
	}

	return 0;
}
