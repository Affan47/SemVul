FreeImage_Invert(FIBITMAP *src) {

	if (!FreeImage_HasPixels(src)) return FALSE;

	unsigned i, x, y, k;

	const unsigned width = FreeImage_GetWidth(src);
	const unsigned height = FreeImage_GetHeight(src);
	const unsigned bpp = FreeImage_GetBPP(src);

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(src);

	if(image_type == FIT_BITMAP) {
		switch(bpp) {
			case 1 :
			case 4 :
			case 8 :
			{


				if (FreeImage_GetColorType(src) == FIC_PALETTE) {
					RGBQUAD *pal = FreeImage_GetPalette(src);

					for(i = 0; i < FreeImage_GetColorsUsed(src); i++) {
						pal[i].rgbRed	= 255 - pal[i].rgbRed;
						pal[i].rgbGreen = 255 - pal[i].rgbGreen;
						pal[i].rgbBlue	= 255 - pal[i].rgbBlue;
					}
				} else {
					for(y = 0; y < height; y++) {
						BYTE *bits = FreeImage_GetScanLine(src, y);

						for (x = 0; x < FreeImage_GetLine(src); x++) {
							bits[x] = ~bits[x];
						}
					}
				}

				break;
			}

			case 24 :
			case 32 :
			{

				const unsigned bytespp = FreeImage_GetLine(src) / width;

				for(y = 0; y < height; y++) {
					BYTE *bits = FreeImage_GetScanLine(src, y);
					for(x = 0; x < width; x++) {
						for(k = 0; k < bytespp; k++) {
							bits[k] = ~bits[k];
						}
						bits += bytespp;
					}
				}

				break;
			}
			default:
				return FALSE;
		}
	}
	else if((image_type == FIT_UINT16) || (image_type == FIT_RGB16) || (image_type == FIT_RGBA16)) {

		const unsigned wordspp = (FreeImage_GetLine(src) / width) / sizeof(WORD);

		for(y = 0; y < height; y++) {
			WORD *bits = (WORD*)FreeImage_GetScanLine(src, y);
			for(x = 0; x < width; x++) {
				for(k = 0; k < wordspp; k++) {
					bits[k] = ~bits[k];
				}
				bits += wordspp;
			}
		}
	}
	else {

		return FALSE;
	}

	return TRUE;
}
