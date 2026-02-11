isFAXImage(TIFF* tif)
{
#ifdef TIFFTAG_FAXRECVPARAMS
    uint32 v;
    if (TIFFGetField(tif, TIFFTAG_FAXRECVPARAMS, &v) && v != 0)
	return (true);
#endif
    uint16 w;
    if (TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &w) && w != 1)
	return (false);
    if (TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &w) && w != 1)
	return (false);
    if (!TIFFGetField(tif, TIFFTAG_COMPRESSION, &w) ||
      (w != COMPRESSION_CCITTFAX3 && w != COMPRESSION_CCITTFAX4))
	return (false);
    if (!TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &w) ||
      (w != PHOTOMETRIC_MINISWHITE && w != PHOTOMETRIC_MINISBLACK))
	return (false);
    return (true);
}
