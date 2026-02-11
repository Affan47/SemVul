PrintCodeBlock(GifFileType *GifFile, GifByteType *CodeBlock, int Reset)
{
    static int CrntPlace = 0, Print = TRUE;
    static long CodeCount = 0;
    int i, Percent, Len;
    long NumBytes;

    if (Reset || CodeBlock == NULL) {
	if (CodeBlock == NULL) {
	    if (CrntPlace > 0) {
		if (Print) printf("\n");
		CodeCount += CrntPlace - 16;
	    }
	    if (GifFile->Image.ColorMap)
		NumBytes = ((((long) GifFile->Image.Width) * GifFile->Image.Height)
				* GifFile->Image.ColorMap->BitsPerPixel) / 8;
	    else
		NumBytes = ((((long) GifFile->Image.Width) * GifFile->Image.Height)
				* GifFile->SColorMap->BitsPerPixel) / 8;
	    Percent = 100 * CodeCount / NumBytes;
	    printf("\nCompression ratio: %ld/%ld (%d%%).\n",
			CodeCount, NumBytes, Percent);
	    return;
	}
	CrntPlace = 0;
	CodeCount = 0;
	Print = TRUE;
    }

    Len = CodeBlock[0];
    for (i = 1; i <= Len; i++) {
	if (CrntPlace == 0) {
	    if (Print) printf("\n%05lxh:  ", CodeCount);
	    CodeCount += 16;
	}
#ifdef __MSDOS__
	if (kbhit() && ((c = getch()) == 'q' || c == 'Q')) Print = FALSE;
#endif
	if (Print) printf(" %02xh", CodeBlock[i]);
	if (++CrntPlace >= 16) CrntPlace = 0;
    }
}
