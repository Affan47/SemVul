rtl_hw_start_8168d_4(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct pci_dev *pdev = tp->pci_dev;
	static const struct ephy_info e_info_8168d_4[] = {
		{ 0x0b, ~0,	0x48 },
		{ 0x19, 0x20,	0x50 },
		{ 0x0c, ~0,	0x20 }
	};
	int i;

	rtl_csi_access_enable_1(tp);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	for (i = 0; i < ARRAY_SIZE(e_info_8168d_4); i++) {
		const struct ephy_info *e = e_info_8168d_4 + i;
		u16 w;

		w = rtl_ephy_read(tp, e->offset);
		rtl_ephy_write(tp, 0x03, (w & e->mask) | e->bits);
	}

	rtl_enable_clock_request(pdev);
}
