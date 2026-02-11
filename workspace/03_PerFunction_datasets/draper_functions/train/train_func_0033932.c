rescale(unsigned new_width, unsigned new_height, FREE_IMAGE_FILTER filter) {
	if(_dib) {
		switch(FreeImage_GetImageType(_dib)) {
			case FIT_BITMAP:
			case FIT_UINT16:
			case FIT_RGB16:
			case FIT_RGBA16:
			case FIT_FLOAT:
			case FIT_RGBF:
			case FIT_RGBAF:
				break;
			default:
				return FALSE;
				break;
		}


		FIBITMAP *dst = FreeImage_Rescale(_dib, new_width, new_height, filter);
		return replace(dst);
	}
	return FALSE;
}
