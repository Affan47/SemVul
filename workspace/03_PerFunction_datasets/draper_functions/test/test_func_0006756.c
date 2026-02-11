LoadDXT (int type, DDSURFACEDESC2 &desc, FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	int width = (int)desc.dwWidth & ~3;
	int height = (int)desc.dwHeight & ~3;


	FIBITMAP *dib = FreeImage_Allocate (width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	if (dib == NULL)
		return NULL;

	int bpp = FreeImage_GetBPP (dib);
	int line = CalculateLine (width, bpp);
	BYTE *bits = FreeImage_GetBits (dib);


	switch (type) {
		case 1:
			LoadDXT_Helper <DXT_BLOCKDECODER_1> (io, handle, page, flags, data, dib, width, height, line);
			break;
		case 3:
			LoadDXT_Helper <DXT_BLOCKDECODER_3> (io, handle, page, flags, data, dib, width, height, line);
			break;
		case 5:
			LoadDXT_Helper <DXT_BLOCKDECODER_5> (io, handle, page, flags, data, dib, width, height, line);
			break;
	}

	return dib;
}
