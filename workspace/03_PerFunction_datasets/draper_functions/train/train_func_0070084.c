sil24_scr_read(struct ata_link *link, unsigned sc_reg, u32 *val)
{
	void __iomem *scr_addr = sil24_port_base(link->ap) + PORT_SCONTROL;

	if (sc_reg < ARRAY_SIZE(sil24_scr_map)) {
		*val = readl(scr_addr + sil24_scr_map[sc_reg] * 4);
		return 0;
	}
	return -EINVAL;
}
