main(int argc, char **argv)
{
    int	Error, NumFiles, ImageWidth, ImageHeight, Dummy, Red, Green, Blue,
	ColorMapSize, InFileHandle,
	ImageSizeFlag = FALSE, ColorMapFlag = FALSE, HelpFlag = FALSE;
    char **FileName = NULL, *ColorMapFile;
    ColorMapObject *ColorMap;
    FILE *InColorMapFile;

    if ((Error = GAGetArgs(argc, argv, CtrlStr, &GifQuietPrint,
		&ImageSizeFlag, &ImageWidth, &ImageHeight,
		&ColorMapFlag, &ColorMapFile,
		&HelpFlag,
		&NumFiles, &FileName)) != FALSE ||
		(NumFiles > 1 && !HelpFlag)) {
	if (Error)
	    GAPrintErrMsg(Error);
	else if (NumFiles > 1)
	    GIF_MESSAGE("Error in command line parsing - one GIF file please.");
	GAPrintHowTo(CtrlStr);
	exit(EXIT_FAILURE);
    }

    if (HelpFlag) {
	fprintf(stderr, "%s", VersionStr);
	GAPrintHowTo(CtrlStr);
	exit(EXIT_SUCCESS);
    }

    if (ColorMapFlag) {

	if ((InColorMapFile = fopen(ColorMapFile, "rt")) == NULL) {
	    GIF_MESSAGE("Failed to open COLOR MAP file (not exists!?).");
	    exit(EXIT_FAILURE);
	}
	if ((ColorMap = MakeMapObject(256, NULL)) == NULL) {
	    GIF_MESSAGE("Failed to allocate bitmap, aborted.");
	    exit(EXIT_FAILURE);
	}

	for (ColorMapSize = 0;
	     ColorMapSize < 256 && !feof(InColorMapFile);
	     ColorMapSize++) {
	    fscanf(InColorMapFile, "%3d %3d %3d %3d\n",
						&Dummy, &Red, &Green, &Blue);
	    ColorMap->Colors[ColorMapSize].Red = Red;
	    ColorMap->Colors[ColorMapSize].Green = Green;
	    ColorMap->Colors[ColorMapSize].Blue = Blue;
	}
    }
    else {
	ColorMap = MakeMapObject(16, EGAPalette);
    }

    if (NumFiles == 1) {
#ifdef __MSDOS__
	if ((InFileHandle = open(*FileName, O_RDONLY | O_BINARY)) == -1) {
#else
	if ((InFileHandle = open(*FileName, O_RDONLY)) == -1) {
#endif
	    GIF_MESSAGE("Failed to open RAW image file (not exists!?).");
	    exit(EXIT_FAILURE);
	}
	dup2(InFileHandle, 0);
    }
    else {
#ifdef __MSDOS__
	setmode(0, O_BINARY);
#endif
    }

#ifdef __MSDOS__
    setvbuf(stdin, NULL, _IOFBF, GIF_FILE_BUFFER_SIZE);
#endif


    Raw2Gif(ImageWidth, ImageHeight, ColorMap);

    return 0;
}
