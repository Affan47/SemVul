sstfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
                           u_int transp, struct fb_info *info)
{
	struct sstfb_par *par = info->par;
	u32 col;

	f_dddprintk("sstfb_setcolreg\n");
	f_dddprintk("%-2d rgbt: %#x, %#x, %#x, %#x\n",
	            regno, red, green, blue, transp);
	if (regno > 15)
		return 0;

	red    >>= (16 - info->var.red.length);
	green  >>= (16 - info->var.green.length);
	blue   >>= (16 - info->var.blue.length);
	transp >>= (16 - info->var.transp.length);
	col = (red << info->var.red.offset)
	    | (green << info->var.green.offset)
	    | (blue  << info->var.blue.offset)
	    | (transp << info->var.transp.offset);

	par->palette[regno] = col;

	return 0;
}
