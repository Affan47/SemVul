_cirrus_write_blt_start(struct cpssp *cpssp, unsigned char val)
{
	unsigned char old_val;

	old_val = cpssp->blt_start_status;
	cpssp->blt_start_status = val;

	if (((old_val & BITBLT_RESET) == 0)
	 && (val & BITBLT_RESET)) {
		_cirrus_bitblt_reset(cpssp);
	} else if (((old_val & BITBLT_START) == 0)
		   && (val & BITBLT_START)) {
		_cirrus_bitblt_start(cpssp);
	}
}
