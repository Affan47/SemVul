ilRegisterPal(void *Pal, ILuint Size, ILenum Type)
{
	if (!iCurImage->Pal.Palette || !iCurImage->Pal.PalSize || iCurImage->Pal.PalType != IL_PAL_NONE) {
		ifree(iCurImage->Pal.Palette);
	}

	iCurImage->Pal.PalSize = Size;
	iCurImage->Pal.PalType = Type;
	iCurImage->Pal.Palette = (ILubyte*)ialloc(Size);
	if (iCurImage->Pal.Palette == NULL)
		return;

	if (Pal != NULL) {
		memcpy(iCurImage->Pal.Palette, Pal, Size);
	}
	else {
		ilSetError(IL_INVALID_PARAM);
	}

	return;
}
