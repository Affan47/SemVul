iCopyPalette(ILpal *Dest, ILpal *Src)
{
	if (Src->Palette == NULL || Src->PalSize == 0)
		return IL_FALSE;

	Dest->Palette = (ILubyte*)ialloc(Src->PalSize);
	if (Dest->Palette == NULL)
		return IL_FALSE;

	memcpy(Dest->Palette, Src->Palette, Src->PalSize);

	Dest->PalSize = Src->PalSize;
	Dest->PalType = Src->PalType;

	return IL_TRUE;
}
