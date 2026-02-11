mv_setup_ifcfg(void __iomem *port_mmio, int want_gen2i)
{
	u32 ifcfg = readl(port_mmio + SATA_IFCFG);

	ifcfg = (ifcfg & 0xf7f) | 0x9b1000;
	if (want_gen2i)
		ifcfg |= (1 << 7);
	writelfl(ifcfg, port_mmio + SATA_IFCFG);
}
