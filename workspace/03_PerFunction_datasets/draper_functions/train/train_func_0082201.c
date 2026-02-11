FreeImage_ConvertLine1To32(BYTE *target, BYTE *source, int width_in_pixels, RGBQUAD *palette) {
	for (int cols = 0; cols < width_in_pixels; cols++) {
		int index = (source[cols>>3] & (0x80 >> (cols & 0x07))) != 0 ? 1 : 0;

		target[FI_RGBA_BLUE]	= palette[index].rgbBlue;
		target[FI_RGBA_GREEN]	= palette[index].rgbGreen;
		target[FI_RGBA_RED]		= palette[index].rgbRed;
		target[FI_RGBA_ALPHA]	= 0xFF;
		target += 4;
	}
}
