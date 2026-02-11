tiffnbsubfiles(const char *fname)
{
    TIFF *tif;
    int   imageindex = 0;

    if ((tif = TIFFOpen(fname, "r")) == NULL) {
	LIARerror("Cannot open file %s", fname);
	return(-1);
    }

    while (TIFFSetDirectory(tif, imageindex))
	imageindex++;

    TIFFClose(tif);

    return imageindex;
}
