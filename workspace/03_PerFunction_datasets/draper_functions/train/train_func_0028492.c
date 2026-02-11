igb_set_pcie_no_snoop_generic(struct e1000_hw *hw, u32 no_snoop)
{
	u32 gcr;

	DEBUGFUNC("igb_set_pcie_no_snoop_generic");

	if (hw->bus.type != e1000_bus_type_pci_express)
		goto out;

	if (no_snoop) {
		gcr = E1000_READ_REG(hw, E1000_GCR);
		gcr &= ~(PCIE_NO_SNOOP_ALL);
		gcr |= no_snoop;
		E1000_WRITE_REG(hw, E1000_GCR, gcr);
	}
out:
	return;
}
