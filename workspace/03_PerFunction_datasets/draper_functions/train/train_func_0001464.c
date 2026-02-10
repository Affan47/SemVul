iReadBwTga(TARGAHEAD *Header)
{
	char ID[255];

	if (iread(ID, 1, Header->IDLen) != Header->IDLen)
		return IL_FALSE;


	if (!ilTexImage(Header->Width, Header->Height, 1, (ILubyte)(Header->Bpp >> 3), IL_LUMINANCE, IL_UNSIGNED_BYTE, NULL)) {
		return IL_FALSE;
	}

	if (Header->ImageType == TGA_BW_COMP) {
		if (!iUncompressTgaData(iCurImage)) {
			return IL_FALSE;
		}
	}
	else {
		if (iread(iCurImage->Data, 1, iCurImage->SizeOfData) != iCurImage->SizeOfData) {
			return IL_FALSE;
		}
	}

	return IL_TRUE;
}
