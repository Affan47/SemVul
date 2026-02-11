StartPage ()
{
    DRIVER_ERROR err;
    BYTE    szCustomSize[16];


	err = thePrinter->Send ((const BYTE*)FrFeedOrientationSeq,sizeof(FrFeedOrientationSeq));
	ERRCHECK;


	PAPER_SIZE ps = thePrintContext->GetPaperSize ();
	int msizeCode = FrPaperToMediaSize(ps);
	FrPaperSizeSeq[1] = (BYTE) msizeCode;
#ifdef APDK_EXTENDED_MEDIASIZE
	if(msizeCode == 96 || msizeCode == 17)
	{
        union
        {
            float       fValue;
            uint32_t    uiValue;
        } LJFUnion;
        uint32_t    uiXsize;
        uint32_t    uiYsize;
        int         k = 0;
        LJFUnion.fValue = (float) thePrintContext->PhysicalPageSizeX ();
        uiXsize = LJFUnion.uiValue;
        LJFUnion.fValue = (float) thePrintContext->PhysicalPageSizeY ();
        uiYsize = LJFUnion.uiValue;
        szCustomSize[k++] = 0xD5;
        szCustomSize[k++] = (BYTE) (uiXsize & 0x000000FF);
        szCustomSize[k++] = (BYTE) ((uiXsize & 0x0000FF00) >> 8);
        szCustomSize[k++] = (BYTE) ((uiXsize & 0x00FF0000) >> 16);
        szCustomSize[k++] = (BYTE) ((uiXsize & 0xFF000000) >> 24);
        szCustomSize[k++] = (BYTE) (uiYsize & 0x000000FF);
        szCustomSize[k++] = (BYTE) ((uiYsize & 0x0000FF00) >> 8);
        szCustomSize[k++] = (BYTE) ((uiYsize & 0x00FF0000) >> 16);
        szCustomSize[k++] = (BYTE) ((uiYsize & 0xFF000000) >> 24);
        szCustomSize[k++] = 0xF8;
        szCustomSize[k++] = 0x2F;
        err = thePrinter->Send ((const BYTE *) szCustomSize, k);
		ERRCHECK;


		BYTE FrCustomMediaSeq[] = {0xC0,0x00, 0xF8, 0x30};
		err = thePrinter->Send ((const BYTE *)FrCustomMediaSeq, sizeof(FrCustomMediaSeq));
		ERRCHECK;
	}
	else
#endif
	{
		err = thePrinter->Send ((const BYTE*)FrPaperSizeSeq,sizeof(FrPaperSizeSeq));
		ERRCHECK;
	}

	err = thePrinter->Send ((const BYTE *)FrBeginPageSeq, sizeof(FrBeginPageSeq));
	ERRCHECK;

	bLastBand = FALSE;

    return err;
}
