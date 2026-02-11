init_display(struct fbtft_par *par)
{
	u8 i;

	par->fbtftops.reset(par);

	for (i = 0; i < 2; ++i) {
		write_reg(par, i, 0x3f);
		write_reg(par, i, 0x40);
		write_reg(par, i, 0xb0);
		write_reg(par, i, 0xc0);
	}

	return 0;
}
