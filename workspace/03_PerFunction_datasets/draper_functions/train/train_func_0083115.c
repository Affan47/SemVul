set_var(struct fbtft_par *par)
{
	u8 val;

	switch (par->info->var.rotate) {
	case 270:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MX;
		break;
	case 180:
		val = 0;
		break;
	case 90:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MY;
		break;
	default:
		val = HX8357D_MADCTL_MX | HX8357D_MADCTL_MY;
		break;
	}

	val |= (par->bgr ? HX8357D_MADCTL_RGB : HX8357D_MADCTL_BGR);


	write_reg(par, HX8357_MADCTL, val);

	return 0;
}
