ilCompressDXT(ILubyte *Data, ILuint Width, ILuint Height, ILuint Depth, ILenum DXTCFormat, ILuint *DXTCSize)
{
	ILimage *TempImage, *CurImage = iCurImage;
	ILuint	BuffSize;
	ILubyte	*Buffer;

	if ((DXTCFormat != IL_DXT1 && DXTCFormat != IL_DXT1A && DXTCFormat != IL_DXT3 && DXTCFormat != IL_DXT5)
		|| Data == NULL || Width == 0 || Height == 0 || Depth == 0) {
		ilSetError(IL_INVALID_PARAM);
		return NULL;
	}


#ifdef IL_USE_DXTC_NVIDIA
	if (ilIsEnabled(IL_NVIDIA_COMPRESS) && Depth == 1) {


		return ilNVidiaCompressDXT(Data, Width, Height, 1, DXTCFormat, DXTCSize);
	}
#endif


#ifdef IL_USE_DXTC_SQUISH
	if (ilIsEnabled(IL_SQUISH_COMPRESS) && Depth == 1) {
		if (DXTCFormat == IL_DXT1 || DXTCFormat == IL_DXT1A || DXTCFormat == IL_DXT3 || DXTCFormat == IL_DXT5) {


			return ilSquishCompressDXT(Data, Width, Height, 1, DXTCFormat, DXTCSize);
		}
	}
#endif

	TempImage = (ILimage*)ialloc(sizeof(ILimage));
	memset(TempImage, 0, sizeof(ILimage));
	TempImage->Width = Width;
	TempImage->Height = Height;
	TempImage->Depth = Depth;
	TempImage->Bpp = 4;
	TempImage->Format = IL_BGRA;
	TempImage->Bpc = 1;
	TempImage->Type = IL_UNSIGNED_BYTE;
	TempImage->SizeOfPlane = TempImage->Bps * Height;
	TempImage->SizeOfData  = TempImage->SizeOfPlane * Depth;
	TempImage->Origin = IL_ORIGIN_UPPER_LEFT;
	TempImage->Data = Data;

	BuffSize = ilGetDXTCData(NULL, 0, DXTCFormat);
	if (BuffSize == 0)
		return NULL;
	Buffer = (ILubyte*)ialloc(BuffSize);
	if (Buffer == NULL)
		return NULL;

	if (ilGetDXTCData(Buffer, BuffSize, DXTCFormat) != BuffSize) {
		ifree(Buffer);
		return NULL;
	}
	*DXTCSize = BuffSize;


	iCurImage = CurImage;
	TempImage->Data = NULL;
	ilCloseImage(TempImage);

	return Buffer;
}
