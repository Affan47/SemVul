sil_scr_read(struct ata_link *link, unsigned int sc_reg, u32 *val)
{
	void __iomem *mmio = sil_scr_addr(link->ap, sc_reg);

	if (mmio) {
		*val = readl(mmio);
		return 0;
	}
	return -EINVAL;
}
