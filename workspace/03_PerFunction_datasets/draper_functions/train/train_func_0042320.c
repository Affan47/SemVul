SwapRedBlue32(FIBITMAP* dib) {
	if(FreeImage_GetImageType(dib) != FIT_BITMAP) {
		return FALSE;
	}

	const unsigned bytesperpixel = FreeImage_GetBPP(dib) / 8;
	if(bytesperpixel > 4 || bytesperpixel < 3) {
		return FALSE;
	}

	const unsigned height = FreeImage_GetHeight(dib);
	const unsigned pitch = FreeImage_GetPitch(dib);
	const unsigned lineSize = FreeImage_GetLine(dib);

	BYTE* line = FreeImage_GetBits(dib);
	for(unsigned y = 0; y < height; ++y, line += pitch) {
		for(BYTE* pixel = line; pixel < line + lineSize ; pixel += bytesperpixel) {
			INPLACESWAP(pixel[0], pixel[2]);
		}
	}

	return TRUE;
}
