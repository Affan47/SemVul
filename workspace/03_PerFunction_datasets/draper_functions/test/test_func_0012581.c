fbtft_fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *info)
{
	unsigned val;
	int ret = 1;

	dev_dbg(info->dev,
		"%s(regno=%u, red=0x%X, green=0x%X, blue=0x%X, trans=0x%X)\n",
		__func__, regno, red, green, blue, transp);

	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			u32 *pal = info->pseudo_palette;

			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);

			pal[regno] = val;
			ret = 0;
		}
		break;

	}
	return ret;
}
