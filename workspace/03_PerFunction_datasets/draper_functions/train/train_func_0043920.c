set_var(struct fbtft_par *par)
{
	switch (par->info->var.rotate) {

	case 0:
		write_reg(par, 0x003, 0x1230);
		break;
	case 180:
		write_reg(par, 0x003, 0x1200);
		break;
	case 270:
		write_reg(par, 0x003, 0x1228);
		break;
	case 90:
		write_reg(par, 0x003, 0x1218);
		break;
	}

	return 0;
}
