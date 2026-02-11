FreeImage_GetComplexChannel(FIBITMAP *src, FREE_IMAGE_COLOR_CHANNEL channel) {
	unsigned x, y;
	double mag, phase;
	FICOMPLEX *src_bits = NULL;
	double *dst_bits = NULL;
	FIBITMAP *dst = NULL;

	if(!FreeImage_HasPixels(src)) return NULL;

	if(FreeImage_GetImageType(src) == FIT_COMPLEX) {

		unsigned width  = FreeImage_GetWidth(src);
		unsigned height = FreeImage_GetHeight(src);
		dst = FreeImage_AllocateT(FIT_DOUBLE, width, height) ;
		if(!dst) return NULL;


		switch(channel) {
			case FICC_REAL:
				for(y = 0; y < height; y++) {
					src_bits = (FICOMPLEX *)FreeImage_GetScanLine(src, y);
					dst_bits = (double *)FreeImage_GetScanLine(dst, y);
					for(x = 0; x < width; x++) {
						dst_bits[x] = src_bits[x].r;
					}
				}
				break;

			case FICC_IMAG:
				for(y = 0; y < height; y++) {
					src_bits = (FICOMPLEX *)FreeImage_GetScanLine(src, y);
					dst_bits = (double *)FreeImage_GetScanLine(dst, y);
					for(x = 0; x < width; x++) {
						dst_bits[x] = src_bits[x].i;
					}
				}
				break;

			case FICC_MAG:
				for(y = 0; y < height; y++) {
					src_bits = (FICOMPLEX *)FreeImage_GetScanLine(src, y);
					dst_bits = (double *)FreeImage_GetScanLine(dst, y);
					for(x = 0; x < width; x++) {
						mag = src_bits[x].r * src_bits[x].r + src_bits[x].i * src_bits[x].i;
						dst_bits[x] = sqrt(mag);
					}
				}
				break;

			case FICC_PHASE:
				for(y = 0; y < height; y++) {
					src_bits = (FICOMPLEX *)FreeImage_GetScanLine(src, y);
					dst_bits = (double *)FreeImage_GetScanLine(dst, y);
					for(x = 0; x < width; x++) {
						if((src_bits[x].r == 0) && (src_bits[x].i == 0)) {
							phase = 0;
						} else {
							phase = atan2(src_bits[x].i, src_bits[x].r);
						}
						dst_bits[x] = phase;
					}
				}
				break;
		}
	}


	FreeImage_CloneMetadata(dst, src);

	return dst;
}
