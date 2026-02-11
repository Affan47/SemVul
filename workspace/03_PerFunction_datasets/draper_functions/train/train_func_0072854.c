_cirrus_vga_by16_writeb(
	struct cpssp *cpssp,
	unsigned long offset,
	uint8_t val,
	int mode)
{
	unsigned long to;
	int x;

#if (1 < CIRRUS_DEBUG)
	faum_log(FAUM_LOG_DEBUG, __FUNCTION__, "",
		 "0x%08lx <- 0x%02hx mode=%d\n",
		 offset, val, mode);
#endif

	to = offset;

	for (x = 0; x < 8; x++) {

		if (val & 0x80) {
			video_writeb(cpssp, to+0, cpssp->shadow_gr1);
			video_writeb(cpssp, to+1, cpssp->blt_color_exp_fg_bg[1]);
		} else if (mode == 5) {
			video_writeb(cpssp, to+0, cpssp->shadow_gr0);
			video_writeb(cpssp, to+1, cpssp->blt_color_exp_fg_bg[0]);
		}

		val <<= 1;
		to += 2;
	}
}
