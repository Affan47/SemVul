TIFFReadEncodedTile(TIFF* tif, uint32 tile, void* buf, tmsize_t size)
{
	static const char module[] = "TIFFReadEncodedTile";
	TIFFDirectory *td = &tif->tif_dir;
	tmsize_t tilesize = tif->tif_tilesize;

	if (!TIFFCheckRead(tif, 1))
		return ((tmsize_t)(-1));
	if (tile >= td->td_nstrips) {
		TIFFErrorExt(tif->tif_clientdata, module,
		    "%lu: Tile out of range, max %lu",
		    (unsigned long) tile, (unsigned long) td->td_nstrips);
		return ((tmsize_t)(-1));
	}
	if (size == (tmsize_t)(-1))
		size = tilesize;
	else if (size > tilesize)
		size = tilesize;
	if (TIFFFillTile(tif, tile) && (*tif->tif_decodetile)(tif,
	    (uint8*) buf, size, (uint16)(tile/td->td_stripsperimage))) {
		(*tif->tif_postdecode)(tif, (uint8*) buf, size);
		return (size);
	} else
		return ((tmsize_t)(-1));
}
