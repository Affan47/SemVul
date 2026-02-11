set_var(struct fbtft_par *par)
{
	switch (par->info->var.rotate) {
	case 0:
		write_reg(par, 0x3, (par->bgr << 12) | 0x30);
		break;
	case 270:
		write_reg(par, 0x3, (par->bgr << 12) | 0x28);
		break;
	case 180:
		write_reg(par, 0x3, (par->bgr << 12) | 0x00);
		break;
	case 90:
		write_reg(par, 0x3, (par->bgr << 12) | 0x18);
		break;
	}
	return 0;
}
