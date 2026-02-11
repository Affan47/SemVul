TIFFCheckpointDirectory(TIFF* tif)
{
	int rc;

	if (tif->tif_dir.td_stripoffset == NULL)
	    (void) TIFFSetupStrips(tif);
	rc = TIFFWriteDirectorySec(tif,TRUE,FALSE,NULL);
	(void) TIFFSetWriteOffset(tif, TIFFSeekFile(tif, 0, SEEK_END));
	return rc;
}
