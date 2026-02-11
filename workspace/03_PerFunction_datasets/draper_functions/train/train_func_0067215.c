ilSetPixels1D(ILint XOff, ILuint Width, void *Data)
{
	ILuint	c, SkipX = 0, PixBpp;
	ILint	x, NewWidth;
	ILubyte	*Temp = (ILubyte*)Data, *TempData = iCurImage->Data;

	if (ilIsEnabled(IL_ORIGIN_SET)) {
		if ((ILenum)ilGetInteger(IL_ORIGIN_MODE) != iCurImage->Origin) {
			TempData = iGetFlipped(iCurImage);
			if (TempData == NULL)
				return IL_FALSE;
		}
	}

	PixBpp = iCurImage->Bpp * iCurImage->Bpc;

	if (XOff < 0) {
		SkipX = abs(XOff);
		XOff = 0;
	}

	if (iCurImage->Width < XOff + Width) {
		NewWidth = iCurImage->Width - XOff;
	}
	else {
		NewWidth = Width;
	}

	NewWidth -= SkipX;

	for (x = 0; x < NewWidth; x++) {
		for (c = 0; c < PixBpp; c++) {
			TempData[(x + XOff) * PixBpp + c] = Temp[(x + SkipX) * PixBpp + c];
		}
	}

	if (TempData != iCurImage->Data) {
		ifree(iCurImage->Data);
		iCurImage->Data = TempData;
	}

	return IL_TRUE;
}
