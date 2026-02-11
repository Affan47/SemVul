rtl_hw_start_8102e_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct pci_dev *pdev = tp->pci_dev;
	static const struct ephy_info e_info_8102e_1[] = {
		{ 0x01,	0, 0x6e65 },
		{ 0x02,	0, 0x091f },
		{ 0x03,	0, 0xc2f9 },
		{ 0x06,	0, 0xafb5 },
		{ 0x07,	0, 0x0e00 },
		{ 0x19,	0, 0xec80 },
		{ 0x01,	0, 0x2e65 },
		{ 0x01,	0, 0x6e65 }
	};
	u8 cfg1;

	rtl_csi_access_enable_2(tp);

	RTL_W8(DBG_REG, FIX_NAK_1);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(Config1,
	       LEDS1 | LEDS0 | Speed_down | MEMMAP | IOMAP | VPD | PMEnable);
	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	cfg1 = RTL_R8(Config1);
	if ((cfg1 & LEDS0) && (cfg1 & LEDS1))
		RTL_W8(Config1, cfg1 & ~LEDS0);

	rtl_ephy_init(tp, e_info_8102e_1, ARRAY_SIZE(e_info_8102e_1));
}
