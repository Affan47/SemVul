get_bitgrid_for_8bit_raster(size_t w, size_t h, const uint8_t *raster, uint8_t wanted) {
	BitGrid mask(w, h);

	const uint8_t *p = raster;
	for(size_t y=0; y<h; y++) {
		for(size_t x=0; x<w; x++) {
			mask.set(x, y, *(p++) == wanted);
		}
	}

	return mask;
}
