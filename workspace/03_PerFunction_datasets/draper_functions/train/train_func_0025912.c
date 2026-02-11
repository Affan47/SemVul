register_mask(void *pixels)
{
	if (mask) {
		free(mask);
		mask = NULL;
	}
	assert(pixels);
	if (scale_up) {
		mask = malloc(screen_pitch*screen_height);
		assert(mask);
		do_scale2x((unsigned char *)pixels, JNB_WIDTH, JNB_HEIGHT, (unsigned char *)mask);
	} else {
		mask = malloc(JNB_WIDTH*JNB_HEIGHT);
		assert(mask);
		memcpy(mask, pixels, JNB_WIDTH*JNB_HEIGHT);
	}
}
