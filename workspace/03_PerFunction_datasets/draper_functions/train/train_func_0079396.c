dwmac1000_pmt(struct mac_device_info *hw, unsigned long mode)
{
	void __iomem *ioaddr = hw->pcsr;
	unsigned int pmt = 0;

	if (mode & WAKE_MAGIC) {
		pr_debug("GMAC: WOL Magic frame\n");
		pmt |= power_down | magic_pkt_en;
	}
	if (mode & WAKE_UCAST) {
		pr_debug("GMAC: WOL on global unicast\n");
		pmt |= global_unicast;
	}

	writel(pmt, ioaddr + GMAC_PMT);
}
