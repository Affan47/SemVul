FreeImage_ConvertLine24To32(BYTE *target, BYTE *source, int width_in_pixels) {
	for (int cols = 0; cols < width_in_pixels; cols++) {
		target[FI_RGBA_RED]   = source[FI_RGBA_RED];
		target[FI_RGBA_GREEN] = source[FI_RGBA_GREEN];
		target[FI_RGBA_BLUE]  = source[FI_RGBA_BLUE];
		target[FI_RGBA_ALPHA] = 0xFF;
		target += 4;
		source += 3;
	}
}
