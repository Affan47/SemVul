be_reg_intr_set(struct be_adapter *adapter, bool enable)
{
	u32 reg, enabled;

	pci_read_config_dword(adapter->pdev, PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET,
			      &reg);
	enabled = reg & MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;

	if (!enabled && enable)
		reg |= MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	else if (enabled && !enable)
		reg &= ~MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	else
		return;

	pci_write_config_dword(adapter->pdev,
			       PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET, reg);
}
