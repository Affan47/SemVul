iIsValidBmp()
{
	BMPHEAD		Head;
	OS2_HEAD	Os2Head;
	ILboolean	IsValid;

	iGetBmpHead(&Head);
	iseek(-(ILint)sizeof(BMPHEAD), IL_SEEK_CUR);

	IsValid = iCheckBmp(&Head);
	if (!IsValid) {
		iGetOS2Head(&Os2Head);
		iseek(-(ILint)sizeof(BMPHEAD), IL_SEEK_CUR);
		IsValid = iCheckOS2(&Os2Head);
	}
	return IsValid;
}
