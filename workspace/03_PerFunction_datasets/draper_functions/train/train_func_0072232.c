k2_sata_scr_write(struct ata_link *link,
			     unsigned int sc_reg, u32 val)
{
	if (sc_reg > SCR_CONTROL)
		return -EINVAL;
	writel(val, link->ap->ioaddr.scr_addr + (sc_reg * 4));
	return 0;
}
