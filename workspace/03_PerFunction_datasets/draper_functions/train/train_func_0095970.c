iLoadIwiInternal(void)
{
	IWIHEAD		Header;
	ILuint		NumMips = 0;
	ILboolean	HasMipmaps = IL_TRUE;
	ILenum		Format;
	ILubyte		Bpp;

	if (iCurImage == NULL) {
		ilSetError(IL_ILLEGAL_OPERATION);
		return IL_FALSE;
	}


	if (!iGetIwiHead(&Header))
		return IL_FALSE;
	if (!iCheckIwi(&Header)) {
		ilSetError(IL_INVALID_FILE_HEADER);
		return IL_FALSE;
	}


	HasMipmaps = ((Header.Flags & 0x03) == 0x03) ? IL_FALSE : IL_TRUE;


	Format = IwiGetFormat(Header.Format, &Bpp);
	if (!ilTexImage(Header.Width, Header.Height, 1, Bpp, Format, IL_UNSIGNED_BYTE, NULL))
		return IL_FALSE;
	iCurImage->Origin = IL_ORIGIN_UPPER_LEFT;
	if (HasMipmaps)
		if (!IwiInitMipmaps(iCurImage, &NumMips))
			return IL_FALSE;
	if (!IwiReadImage(iCurImage, &Header, NumMips))
		return IL_FALSE;

	return ilFixImage();
}
