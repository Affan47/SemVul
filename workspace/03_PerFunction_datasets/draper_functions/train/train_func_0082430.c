pd_wait_for(struct pd_unit *disk, int w, char *msg)
{
	int k, r, e;

	k = 0;
	while (k < PD_SPIN) {
		r = status_reg(disk);
		k++;
		if (((r & w) == w) && !(r & STAT_BUSY))
			break;
		udelay(PD_SPIN_DEL);
	}
	e = (read_reg(disk, 1) << 8) + read_reg(disk, 7);
	if (k >= PD_SPIN)
		e |= ERR_TMO;
	if ((e & (STAT_ERR | ERR_TMO)) && (msg != NULL))
		pd_print_error(disk, msg, e);
	return e;
}
