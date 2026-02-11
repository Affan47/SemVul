FreeImage_ConvertLine16To8_555(BYTE *target, BYTE *source, int width_in_pixels) {
	const WORD *const bits = (WORD *)source;
	for (unsigned cols = 0; cols < (unsigned)width_in_pixels; cols++) {
		target[cols] = GREY((((bits[cols] & FI16_555_RED_MASK) >> FI16_555_RED_SHIFT) * 0xFF) / 0x1F,
			                (((bits[cols] & FI16_555_GREEN_MASK) >> FI16_555_GREEN_SHIFT) * 0xFF) / 0x1F,
							(((bits[cols] & FI16_555_BLUE_MASK) >> FI16_555_BLUE_SHIFT) * 0xFF) / 0x1F);
	}
}
