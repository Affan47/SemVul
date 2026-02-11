iluConvolution(ILint *matrix, ILint scale, ILint bias) {
	ILubyte		*Data;
	ILboolean	Palette = IL_FALSE, Converted = IL_FALSE;
	ILenum		Type = 0;
	ILimage		*iluCurImage = ilGetCurImage();

	if (iluCurImage == NULL) {
		ilSetError(ILU_ILLEGAL_OPERATION);
		return IL_FALSE;
	}

	if (iluCurImage->Format == IL_COLOUR_INDEX) {
		Palette = IL_TRUE;
		ilConvertImage(ilGetPalBaseType(iluCurImage->Pal.PalType), IL_UNSIGNED_BYTE);
	} else if (iluCurImage->Type > IL_UNSIGNED_BYTE) {
		Converted = IL_TRUE;
		Type = iluCurImage->Type;
		ilConvertImage(iluCurImage->Format, IL_UNSIGNED_BYTE);
	}

	Data = Filter(iluCurImage, matrix, scale, bias);
	if (!Data)
		return IL_FALSE;
	ifree(iluCurImage->Data);
	iluCurImage->Data = Data;

	if (Palette)
		ilConvertImage(IL_COLOUR_INDEX, IL_UNSIGNED_BYTE);
	else if (Converted)
		ilConvertImage(iluCurImage->Format, Type);

	return IL_TRUE;
}
