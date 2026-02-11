screen_align()
{
	for (u16 y = 0; y < height; y++) {
		u32 yp = linenumbers[y] * max_width;
		changed_line(y, 0, width - 1);

		for (u16 x = 0; x < width; x++) {
			text[yp + x] = 'E';
			attrs[yp + x] = normal_char_attr();
		}
	}
}
