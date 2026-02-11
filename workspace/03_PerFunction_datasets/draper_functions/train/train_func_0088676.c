GetUtxName(UTXHEADER &Header)
{
#define NAME_MAX_LEN 256
	char	Name[NAME_MAX_LEN];
	ILubyte	Length = 0;


	if (Header.Version >= 64) {
		Length = igetc();
		if (iread(Name, Length, 1) != 1)
			return "";
		if (Name[Length-1] != 0)
			return "";
		return string(Name);
	}


	do {
		Name[Length++] = igetc();
	} while (!ieof() && Name[Length-1] != 0 && Length < NAME_MAX_LEN);


	if (Length == NAME_MAX_LEN && Name[Length-1] != 0)
		return "";

	return string(Name);
#undef NAME_MAX_LEN
}
