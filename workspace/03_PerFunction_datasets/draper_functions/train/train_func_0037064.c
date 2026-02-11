TIFFCheckTile(TIFF* tif, uint32 x, uint32 y, uint32 z, uint16 s)
{
	TIFFDirectory *td = &tif->tif_dir;

	if (x >= td->td_imagewidth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Col out of range, max %lu",
			     (unsigned long) x,
			     (unsigned long) (td->td_imagewidth - 1));
		return (0);
	}
	if (y >= td->td_imagelength) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Row out of range, max %lu",
			     (unsigned long) y,
			     (unsigned long) (td->td_imagelength - 1));
		return (0);
	}
	if (z >= td->td_imagedepth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Depth out of range, max %lu",
			     (unsigned long) z,
			     (unsigned long) (td->td_imagedepth - 1));
		return (0);
	}
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE &&
	    s >= td->td_samplesperpixel) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Sample out of range, max %lu",
			     (unsigned long) s,
			     (unsigned long) (td->td_samplesperpixel - 1));
		return (0);
	}
	return (1);
}
