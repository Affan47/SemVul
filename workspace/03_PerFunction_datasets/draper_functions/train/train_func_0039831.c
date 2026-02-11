get_std_timing(unsigned char *block, struct fb_videomode *mode,
			  int ver, int rev, const struct fb_monspecs *specs)
{
	int i;

	for (i = 0; i < DMT_SIZE; i++) {
		u32 std_2byte_code = block[0] << 8 | block[1];
		if (std_2byte_code == dmt_modes[i].std_2byte_code)
			break;
	}

	if (i < DMT_SIZE && dmt_modes[i].mode) {

		*mode = *dmt_modes[i].mode;
		mode->flag |= FB_MODE_IS_STANDARD;
		DPRINTK("        DMT id=%d\n", dmt_modes[i].dmt_id);

	} else {
		int xres, yres = 0, refresh, ratio;

		xres = (block[0] + 31) * 8;
		if (xres <= 256)
			return 0;

		ratio = (block[1] & 0xc0) >> 6;
		switch (ratio) {
		case 0:

			if (ver < 1 || (ver == 1 && rev < 3))
				yres = xres;
			else
				yres = (xres * 10)/16;
			break;
		case 1:
			yres = (xres * 3)/4;
			break;
		case 2:
			yres = (xres * 4)/5;
			break;
		case 3:
			yres = (xres * 9)/16;
			break;
		}
		refresh = (block[1] & 0x3f) + 60;
		DPRINTK("      %dx%d@%dHz\n", xres, yres, refresh);

		calc_mode_timings(xres, yres, refresh, mode);
	}


	if (specs && specs->dclkmax
	    && PICOS2KHZ(mode->pixclock) * 1000 > specs->dclkmax) {
		DPRINTK("        mode exceed max DCLK\n");
		return 0;
	}

	return 1;
}
