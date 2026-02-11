iInitDocumentDOS(FILE *pFile, long lFilesize)
{
	int	iWordVersion;
	BOOL	bSuccess;
	USHORT	usIdent;
	UCHAR	aucHeader[128];

	fail(pFile == NULL);

	if (lFilesize < 128) {
		return -1;
	}


	if (!bReadBytes(aucHeader, 128, 0x00, pFile)) {
		return -1;
	}

	usIdent = usGetWord(0x00, aucHeader);
	DBG_HEX(usIdent);
	fail(usIdent != 0xbe31);
	iWordVersion = iGetVersionNumber(aucHeader);
	if (iWordVersion != 0) {
		werr(0, "This file is not from 'Word for DOS'.");
		return -1;
	}
	bSuccess = bGetDocumentText(pFile, lFilesize, aucHeader);
	if (bSuccess) {
		vGetPropertyInfo(pFile, NULL,
				NULL, 0, NULL, 0,
				aucHeader, iWordVersion);
		vSetDefaultTabWidth(pFile, NULL,
				NULL, 0, NULL, 0,
				aucHeader, iWordVersion);
		vGetNotesInfo(pFile, NULL,
				NULL, 0, NULL, 0,
				aucHeader, iWordVersion);
	}
	return bSuccess ? iWordVersion : -1;
}
