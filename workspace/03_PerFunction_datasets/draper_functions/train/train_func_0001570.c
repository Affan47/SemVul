combineChannels(fipImage& red, fipImage& green, fipImage& blue) {
	if(!_dib) {
		int width = red.getWidth();
		int height = red.getHeight();
		_dib = FreeImage_Allocate(width, height, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	}

	if(_dib) {
		BOOL bResult = TRUE;
		bResult &= FreeImage_SetChannel(_dib, red._dib, FICC_RED);
		bResult &= FreeImage_SetChannel(_dib, green._dib, FICC_GREEN);
		bResult &= FreeImage_SetChannel(_dib, blue._dib, FICC_BLUE);

		_bHasChanged = TRUE;

		return bResult;
	}
	return FALSE;
}
