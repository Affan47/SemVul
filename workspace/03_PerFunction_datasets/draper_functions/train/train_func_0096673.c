WHDR(const struct cirrusfb_info *cinfo, unsigned char val)
{
	unsigned char dummy;

	if (is_laguna(cinfo))
		return;
	if (cinfo->btype == BT_PICASSO) {


		WGen(cinfo, VGA_PEL_MSK, 0x00);
		udelay(200);

		dummy = RGen(cinfo, VGA_PEL_IW);
		udelay(200);
	}


	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);

	WGen(cinfo, VGA_PEL_MSK, val);
	udelay(200);

	if (cinfo->btype == BT_PICASSO) {

		dummy = RGen(cinfo, VGA_PEL_IW);
		udelay(200);


		WGen(cinfo, VGA_PEL_MSK, 0xff);
		udelay(200);
	}
}
