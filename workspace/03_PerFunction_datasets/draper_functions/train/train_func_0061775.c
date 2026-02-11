_cirrus_read_palette_data(struct cpssp *cpssp)
{
	unsigned char value;

	if (cpssp->ext_graph_curs_attr & ALLOW_ACCESS_TO_DAC_EXTENDED_COLORS) {
		switch (cpssp->vga.col_reg_03c7 & DAC_EXTENDED_COLOR_MASK) {
		case 0x00:
			value = video_col_get(cpssp, 256, cpssp->vga.col_reg_03c7_rgb)
				>> 2;
			break;
		case 0x0f:
			value = video_col_get(cpssp, 257, cpssp->vga.col_reg_03c7_rgb)
				>> 2;
			break;
		case 0x02:
			value = video_col_get(cpssp, 258, cpssp->vga.col_reg_03c7_rgb)
				>> 2;
			break;
		default:
			faum_log(FAUM_LOG_WARNING, __FUNCTION__, "",
				 "Read access to dac extended colors but "
				 "col_reg_03c7 is 0x%02hx\n",
				 (int) (cpssp->vga.col_reg_03c7 &
					DAC_EXTENDED_COLOR_MASK));
			value = 0x00;
		}
	} else {
		value = video_col_get(cpssp, cpssp->vga.col_reg_03c7,
					cpssp->vga.col_reg_03c7_rgb) >> 2;
	}

	cpssp->vga.col_reg_03c7_rgb++;
	if (cpssp->vga.col_reg_03c7_rgb == 3) {
		cpssp->vga.col_reg_03c7_rgb = 0;
		cpssp->vga.col_reg_03c7++;
	}

	return value;
}
