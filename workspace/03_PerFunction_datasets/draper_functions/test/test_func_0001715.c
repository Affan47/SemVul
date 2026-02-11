iIsValidHdr()
{
	char	Head[10];
	ILint	Read;

	Read = iread(Head, 1, 10);
	iseek(-Read, IL_SEEK_CUR);
	if (Read != 10)
		return IL_FALSE;

	return
		strnicmp(Head, "#?RADIANCE", 10) == 0
		|| strnicmp(Head, "#?RGBE", 6) == 0;
}
