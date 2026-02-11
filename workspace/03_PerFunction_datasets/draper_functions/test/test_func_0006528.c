FreeImage_ConvertLine24To4(BYTE *target, BYTE *source, int width_in_pixels) {
	BOOL hinibble = TRUE;

	for (int cols = 0; cols < width_in_pixels; cols++) {
		if (hinibble) {
			target[cols >> 1] = GREY(source[FI_RGBA_RED], source[FI_RGBA_GREEN], source[FI_RGBA_BLUE]) & 0xF0;
		} else {
			target[cols >> 1] |= GREY(source[FI_RGBA_RED], source[FI_RGBA_GREEN], source[FI_RGBA_BLUE]) >> 4;
		}

		source += 3;
		hinibble = !hinibble;
	}
}
