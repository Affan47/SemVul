matroxfb_pitch_adjust(const struct matrox_fb_info *minfo, int xres,
				 int bpp)
{
	const int* width;
	int xres_new;

	DBG(__func__)

	if (!bpp) return xres;

	width = minfo->capable.vxres;

	if (minfo->devflags.precise_width) {
		while (*width) {
			if ((*width >= xres) && (matroxfb_test_and_set_rounding(minfo, *width, bpp) == *width)) {
				break;
			}
			width++;
		}
		xres_new = *width;
	} else {
		xres_new = matroxfb_test_and_set_rounding(minfo, xres, bpp);
	}
	return xres_new;
}
