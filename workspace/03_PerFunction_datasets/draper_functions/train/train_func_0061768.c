PackBitsPreEncode(TIFF* tif, tsample_t s)
{
        (void) s;

        if (!(tif->tif_data = (tidata_t)_TIFFmalloc(sizeof(tsize_t))))
                return (0);


        if (isTiled(tif))
                *(tsize_t*)tif->tif_data = TIFFTileRowSize(tif);
        else
                *(tsize_t*)tif->tif_data = TIFFScanlineSize(tif);
        return (1);
}
