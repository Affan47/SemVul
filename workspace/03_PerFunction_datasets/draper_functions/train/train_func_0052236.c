iLoadFtxInternal(void)
{
	ILuint Width, Height, HasAlpha;

	if (iCurImage == NULL) {
		ilSetError(IL_ILLEGAL_OPERATION);
		return IL_FALSE;
	}

	Width = GetLittleUInt();
	Height = GetLittleUInt();
	HasAlpha = GetLittleUInt();


		if (!ilTexImage(Width, Height, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, NULL))
			return IL_FALSE;


	iCurImage->Origin = IL_ORIGIN_UPPER_LEFT;


	if (iread(iCurImage->Data, 1, iCurImage->SizeOfData) != iCurImage->SizeOfData)
		return IL_FALSE;

	return ilFixImage();
}
