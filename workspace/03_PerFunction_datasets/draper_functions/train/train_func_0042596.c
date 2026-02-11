sis_scr_write(struct ata_link *link, unsigned int sc_reg, u32 val)
{
	struct ata_port *ap = link->ap;
	void __iomem *base = ap->ioaddr.scr_addr + link->pmp * 0x10;

	if (sc_reg > SCR_CONTROL)
		return -EINVAL;

	if (ap->flags & SIS_FLAG_CFGSCR)
		return sis_scr_cfg_write(link, sc_reg, val);

	iowrite32(val, base + (sc_reg * 4));
	return 0;
}
