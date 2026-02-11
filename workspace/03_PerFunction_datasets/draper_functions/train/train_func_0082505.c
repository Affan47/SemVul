ilSetPixels(ILint XOff, ILint YOff, ILint ZOff, ILuint Width, ILuint Height, ILuint Depth, ILenum Format, ILenum Type, void *Data)
{
	void *Converted;

	if (iCurImage == NULL) {
		ilSetError(IL_ILLEGAL_OPERATION);
		return;
	}
	if (Data == NULL) {
		ilSetError(IL_INVALID_PARAM);
		return;
	}

	if (Format == iCurImage->Format && Type == iCurImage->Type) {
		Converted = (void*)Data;
	}
	else {
		Converted = ilConvertBuffer(Width * Height * Depth * ilGetBppFormat(Format) * ilGetBpcType(Type), Format, iCurImage->Format, Type, iCurImage->Type, NULL, Data);
		if (!Converted)
			return;
	}

	if (YOff + Height <= 1) {
		ilSetPixels1D(XOff, Width, Converted);
	}
	else if (ZOff + Depth <= 1) {
		ilSetPixels2D(XOff, YOff, Width, Height, Converted);
	}
	else {
		ilSetPixels3D(XOff, YOff, ZOff, Width, Height, Depth, Converted);
	}

	if (Format == iCurImage->Format && Type == iCurImage->Type) {
		return;
	}

	if (Converted != Data)
		ifree(Converted);

	return;
}
