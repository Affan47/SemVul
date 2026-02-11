ilSavePnmL(void *Lump, ILuint Size)
{
	ILuint Pos;
	FName = NULL;
	iSetOutputLump(Lump, Size);
	Pos = itellw();
	if (iSavePnmInternal() == IL_FALSE)
		return 0;
	return itellw() - Pos;
}
