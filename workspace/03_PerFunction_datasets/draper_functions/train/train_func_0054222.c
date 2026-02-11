iReadNonRleSgi(iSgiHeader *Head)
{
	ILuint		i, c;

	ILint 		ChanSize;
	ILboolean	Cache = IL_FALSE;

	if (!iNewSgi(Head)) {
		return IL_FALSE;
	}

	if (iGetHint(IL_MEM_SPEED_HINT) == IL_FASTEST) {
		Cache = IL_TRUE;
		ChanSize = Head->XSize * Head->YSize * Head->Bpc;
		iPreCache(ChanSize);
	}

	for (c = 0; c < iCurImage->Bpp; c++) {
		for (i = c; i < iCurImage->SizeOfData; i += iCurImage->Bpp) {
			if (iread(iCurImage->Data + i, 1, 1) != 1) {
				if (Cache)
					iUnCache();
				return IL_FALSE;
			}
		}
	}

	if (Cache)
		iUnCache();

	return IL_TRUE;
}
