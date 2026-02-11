TIFFInitCCITTFax3(TIFF* tif, int scheme)
{
	(void) scheme;
	if (InitCCITTFax3(tif)) {


		if (!_TIFFMergeFields(tif, fax3Fields,
				      TIFFArrayCount(fax3Fields))) {
			TIFFErrorExt(tif->tif_clientdata, "TIFFInitCCITTFax3",
			"Merging CCITT Fax 3 codec-specific tags failed");
			return 0;
		}


		return TIFFSetField(tif, TIFFTAG_FAXMODE, FAXMODE_CLASSF);
	} else
		return 01;
}
