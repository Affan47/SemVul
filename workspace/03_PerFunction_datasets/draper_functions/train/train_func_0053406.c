iluGammaCorrect(ILfloat Gamma)
{
	ILfloat		Table[256];
	ILuint		i, NumPix;
	ILushort	*ShortPtr;
	ILuint		*IntPtr;

	iluCurImage = ilGetCurImage();
	if (iluCurImage == NULL) {
		ilSetError(ILU_ILLEGAL_OPERATION);
		return IL_FALSE;
	}

	for (i = 0; i < 256; i++) {
		Table[i] = (ILfloat)pow(i / 255.0, 1.0 / Gamma);
	}


	if (iluCurImage->Format == IL_COLOUR_INDEX) {
		for (i = 0; i < iluCurImage->Pal.PalSize; i++) {
			iluCurImage->Pal.Palette[i] = (ILubyte)(Table[iluCurImage->Pal.Palette[i]] * 255);
		}
	}
	else {

		switch (iluCurImage->Bpc)
		{
			case 1:
				for (i = 0; i < iluCurImage->SizeOfData; i++) {
					iluCurImage->Data[i] = (ILubyte)(Table[iluCurImage->Data[i]] * UCHAR_MAX);
				}
				break;
			case 2:
				NumPix = iluCurImage->SizeOfData / 2;
				ShortPtr = (ILushort*)iluCurImage->Data;
				for (i = 0; i < NumPix; i++) {
					ShortPtr[i] = (ILushort)(Table[ShortPtr[i] >> 8] * USHRT_MAX);
				}
				break;
			case 4:
				NumPix = iluCurImage->SizeOfData / 4;
				IntPtr = (ILuint*)iluCurImage->Data;
				for (i = 0; i < NumPix; i++) {
					IntPtr[i] = (ILuint)(Table[IntPtr[i] >> 24] * UINT_MAX);
				}
				break;
		}
	}

	return IL_TRUE;
}
