ilSaveTargaF(ILHANDLE File)
{
	ILuint Pos;
	iSetOutputFile(File);
	Pos = itellw();
	if (iSaveTargaInternal() == IL_FALSE)
		return 0;
	return itellw() - Pos;
}
