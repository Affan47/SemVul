load_comp_py_px_reverse(const uint8_t **image_in) {
	*image_in += CHANNELS_RGB;
	comp_t c = 0;
	for (int j = 0; j < CHANNELS_RGB; j++) {
		c <<= CHANNEL_WIDTH_RGB;
		c |= *((*image_in)--);
	}
	*image_in += CHANNELS_RGB;
	return c;
}
