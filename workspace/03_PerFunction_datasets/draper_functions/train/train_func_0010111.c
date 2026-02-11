parport_mos7715_data_reverse(struct parport *pp)
{
	struct mos7715_parport *mos_parport = pp->private_data;

	if (parport_prologue(pp) < 0)
		return;
	mos7715_change_mode(mos_parport, PS2);
	mos_parport->shadowDCR |= 0x20;
	write_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shadowDCR);
	parport_epilogue(pp);
}
