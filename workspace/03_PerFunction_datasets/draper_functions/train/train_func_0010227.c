VerticalSkew(FIBITMAP *src, FIBITMAP *dst, int col, int iOffset, double dWeight, const void *bkcolor) {
	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(src);

	switch(image_type) {
		case FIT_BITMAP:
			switch(FreeImage_GetBPP(src)) {
				case 8:
				case 24:
				case 32:
					VerticalSkewT<BYTE>(src, dst, col, iOffset, dWeight, bkcolor);
					break;
			}
			break;
			case FIT_UINT16:
			case FIT_RGB16:
			case FIT_RGBA16:
				VerticalSkewT<WORD>(src, dst, col, iOffset, dWeight, bkcolor);
				break;
			case FIT_FLOAT:
			case FIT_RGBF:
			case FIT_RGBAF:
				VerticalSkewT<float>(src, dst, col, iOffset, dWeight, bkcolor);
				break;
	}
}
