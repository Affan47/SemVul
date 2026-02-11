ixgbe_pcie_timeout_poll(struct ixgbe_hw *hw)
{
	s16 devctl2;
	u32 pollcnt;

	devctl2 = ixgbe_read_pci_cfg_word(hw, IXGBE_PCI_DEVICE_CONTROL2);
	devctl2 &= IXGBE_PCIDEVCTRL2_TIMEO_MASK;

	switch (devctl2) {
	case IXGBE_PCIDEVCTRL2_65_130ms:
		 pollcnt = 1300;
		break;
	case IXGBE_PCIDEVCTRL2_260_520ms:
		pollcnt = 5200;
		break;
	case IXGBE_PCIDEVCTRL2_1_2s:
		pollcnt = 20000;
		break;
	case IXGBE_PCIDEVCTRL2_4_8s:
		pollcnt = 80000;
		break;
	case IXGBE_PCIDEVCTRL2_17_34s:
		pollcnt = 34000;
		break;
	case IXGBE_PCIDEVCTRL2_50_100us:
	case IXGBE_PCIDEVCTRL2_1_2ms:
	case IXGBE_PCIDEVCTRL2_16_32ms:
	case IXGBE_PCIDEVCTRL2_16_32ms_def:
	default:
		pollcnt = 800;
		break;
	}


	return (pollcnt * 11) / 10;
}
