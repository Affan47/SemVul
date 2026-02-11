uli_scr_write(struct ata_link *link, unsigned int sc_reg, u32 val)
{
	if (sc_reg > SCR_CONTROL)
		return -EINVAL;

	uli_scr_cfg_write(link, sc_reg, val);
	return 0;
}
