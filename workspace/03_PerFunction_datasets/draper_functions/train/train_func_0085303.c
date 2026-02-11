ilResizeImage(ILimage *Image, ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILubyte Bpc)
{
	if (Image == NULL) {
		ilSetError(IL_INVALID_PARAM);
		return IL_FALSE;
	}

	if (Image->Data != NULL)
		ifree(Image->Data);

	Image->Depth = Depth;
	Image->Width = Width;
	Image->Height = Height;
	Image->Bpp = Bpp;
	Image->Bpc = Bpc;
	Image->Bps = Bpp * Bpc * Width;
	Image->SizeOfPlane = Image->Bps * Height;
	Image->SizeOfData = Image->SizeOfPlane * Depth;

	Image->Data = (ILubyte*)ialloc(Image->SizeOfData);
	if (Image->Data == NULL) {
		return IL_FALSE;
	}

	return IL_TRUE;
}
