StripBasedXform(cmsHTRANSFORM hXForm, TIFF* in, TIFF* out, int nPlanes)
{
    tsize_t BufSizeIn  = TIFFStripSize(in);
    tsize_t BufSizeOut = TIFFStripSize(out);
    unsigned char *BufferIn, *BufferOut;
    ttile_t i, StripCount = TIFFNumberOfStrips(in) / nPlanes;
    uint32 sw;
    uint32 sl;
    uint32 iml;
    int j;
    int PixelCount;

    TIFFGetFieldDefaulted(in, TIFFTAG_IMAGEWIDTH,  &sw);
    TIFFGetFieldDefaulted(in, TIFFTAG_ROWSPERSTRIP, &sl);
    TIFFGetFieldDefaulted(in, TIFFTAG_IMAGELENGTH, &iml);


    if (sl == 0 || sl > iml)
        sl = iml;

    BufferIn = (unsigned char *) _TIFFmalloc(BufSizeIn * nPlanes);
    if (!BufferIn) OutOfMem(BufSizeIn * nPlanes);

    BufferOut = (unsigned char *) _TIFFmalloc(BufSizeOut * nPlanes);
    if (!BufferOut) OutOfMem(BufSizeOut * nPlanes);


    for (i = 0; i < StripCount; i++) {

        for (j=0; j < nPlanes; j++) {

            if (TIFFReadEncodedStrip(in, i + (j * StripCount),
                BufferIn + (j * BufSizeIn), BufSizeIn) < 0)   goto cleanup;
        }

        PixelCount = (int) sw * (iml < sl ? iml : sl);
        iml -= sl;

        cmsDoTransform(hXForm, BufferIn, BufferOut, PixelCount);

        for (j=0; j < nPlanes; j++) {
            if (TIFFWriteEncodedStrip(out, i + (j * StripCount),
                BufferOut + j * BufSizeOut, BufSizeOut) < 0) goto cleanup;
        }

    }

    _TIFFfree(BufferIn);
    _TIFFfree(BufferOut);
    return 1;

cleanup:

    _TIFFfree(BufferIn);
    _TIFFfree(BufferOut);
    return 0;
}
