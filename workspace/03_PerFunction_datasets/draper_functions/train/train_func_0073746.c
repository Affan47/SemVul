video_border_pixel_write(Kimage *kimage_ptr, int starty, int num_lines,
			word32 val, int st_off, int end_off)
{
	word32	*ptr;
	int	width;
	int	width_act;
	int	mdepth;
	int	num_words, num_bytes;
	int	bytes_per_pix;
	int	i, j;

	if(end_off <= st_off) {
		return;
	}

	width = end_off - st_off;
	width_act = kimage_ptr->width_act;
	mdepth = kimage_ptr->mdepth;
	bytes_per_pix = mdepth >> 3;
	num_bytes = width * bytes_per_pix;
	num_words = num_bytes >> 2;

	if(width > width_act) {
		halt_printf("border write but width %d > act %d\n", width,
				width_act);
	}

	if(mdepth == 16) {
		val = g_a2palette_8to1624[val & 0xff];
		val = (val << 16) + val;
	} else if(mdepth == 32) {

		val = g_a2palette_8to1624[val & 0xff];
	}

	for(i = 0; i < num_lines; i++) {
		ptr = (word32 *)&(kimage_ptr->data_ptr[
					(starty + i)*width_act*bytes_per_pix]);
		ptr += ((st_off * bytes_per_pix) / 4);


		for(j = 0; j < num_words; j++) {
			*ptr++ = val;
		}
	}
}
