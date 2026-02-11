TIFFInitJPEG(TIFF* tif, int scheme)
{
	JPEGState* sp;

	assert(scheme == COMPRESSION_JPEG);


	if (!_TIFFMergeFields(tif, jpegFields, TIFFArrayCount(jpegFields))) {
		TIFFErrorExt(tif->tif_clientdata,
			     "TIFFInitJPEG",
			     "Merging JPEG codec-specific tags failed");
		return 0;
	}


	tif->tif_data = (uint8*) _TIFFmalloc(sizeof (JPEGState));

	if (tif->tif_data == NULL) {
		TIFFErrorExt(tif->tif_clientdata,
			     "TIFFInitJPEG", "No space for JPEG state block");
		return 0;
	}
        _TIFFmemset(tif->tif_data, 0, sizeof(JPEGState));

	sp = JState(tif);
	sp->tif = tif;


	sp->vgetparent = tif->tif_tagmethods.vgetfield;
	tif->tif_tagmethods.vgetfield = JPEGVGetField;
	sp->vsetparent = tif->tif_tagmethods.vsetfield;
	tif->tif_tagmethods.vsetfield = JPEGVSetField;
	sp->printdir = tif->tif_tagmethods.printdir;
	tif->tif_tagmethods.printdir = JPEGPrintDir;


	sp->jpegtables = NULL;
	sp->jpegtables_length = 0;
	sp->jpegquality = 75;
	sp->jpegcolormode = JPEGCOLORMODE_RAW;
	sp->jpegtablesmode = JPEGTABLESMODE_QUANT | JPEGTABLESMODE_HUFF;
        sp->ycbcrsampling_fetched = 0;


	tif->tif_fixuptags = JPEGFixupTags;
	tif->tif_setupdecode = JPEGSetupDecode;
	tif->tif_predecode = JPEGPreDecode;
	tif->tif_decoderow = JPEGDecode;
	tif->tif_decodestrip = JPEGDecode;
	tif->tif_decodetile = JPEGDecode;
	tif->tif_setupencode = JPEGSetupEncode;
	tif->tif_preencode = JPEGPreEncode;
	tif->tif_postencode = JPEGPostEncode;
	tif->tif_encoderow = JPEGEncode;
	tif->tif_encodestrip = JPEGEncode;
	tif->tif_encodetile = JPEGEncode;
	tif->tif_cleanup = JPEGCleanup;
	sp->defsparent = tif->tif_defstripsize;
	tif->tif_defstripsize = JPEGDefaultStripSize;
	sp->deftparent = tif->tif_deftilesize;
	tif->tif_deftilesize = JPEGDefaultTileSize;
	tif->tif_flags |= TIFF_NOBITREV;

        sp->cinfo_initialized = FALSE;


        if( tif->tif_diroff == 0 )
        {
#define SIZE_OF_JPEGTABLES 2000


            sp->jpegtables_length = SIZE_OF_JPEGTABLES;
            sp->jpegtables = (void *) _TIFFmalloc(sp->jpegtables_length);

	    _TIFFmemset(sp->jpegtables, 0, SIZE_OF_JPEGTABLES);
#undef SIZE_OF_JPEGTABLES
        }

	return 1;
}
