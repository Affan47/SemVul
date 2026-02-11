InitCCITTFax3(TIFF* tif)
{
	static const char module[] = "InitCCITTFax3";
	Fax3BaseState* sp;


	if (!_TIFFMergeFields(tif, faxFields, TIFFArrayCount(faxFields))) {
		TIFFErrorExt(tif->tif_clientdata, "InitCCITTFax3",
			"Merging common CCITT Fax codec-specific tags failed");
		return 0;
	}


	tif->tif_data = (uint8*)
		_TIFFmalloc(sizeof (Fax3CodecState));

	if (tif->tif_data == NULL) {
		TIFFErrorExt(tif->tif_clientdata, module,
		    "No space for state block");
		return (0);
	}

	sp = Fax3State(tif);
        sp->rw_mode = tif->tif_mode;


	sp->vgetparent = tif->tif_tagmethods.vgetfield;
	tif->tif_tagmethods.vgetfield = Fax3VGetField;
	sp->vsetparent = tif->tif_tagmethods.vsetfield;
	tif->tif_tagmethods.vsetfield = Fax3VSetField;
	sp->printdir = tif->tif_tagmethods.printdir;
	tif->tif_tagmethods.printdir = Fax3PrintDir;
	sp->groupoptions = 0;

	if (sp->rw_mode == O_RDONLY)
		tif->tif_flags |= TIFF_NOBITREV;
	DecoderState(tif)->runs = NULL;
	TIFFSetField(tif, TIFFTAG_FAXFILLFUNC, _TIFFFax3fillruns);
	EncoderState(tif)->refline = NULL;


	tif->tif_fixuptags = Fax3FixupTags;
	tif->tif_setupdecode = Fax3SetupState;
	tif->tif_predecode = Fax3PreDecode;
	tif->tif_decoderow = Fax3Decode1D;
	tif->tif_decodestrip = Fax3Decode1D;
	tif->tif_decodetile = Fax3Decode1D;
	tif->tif_setupencode = Fax3SetupState;
	tif->tif_preencode = Fax3PreEncode;
	tif->tif_postencode = Fax3PostEncode;
	tif->tif_encoderow = Fax3Encode;
	tif->tif_encodestrip = Fax3Encode;
	tif->tif_encodetile = Fax3Encode;
	tif->tif_close = Fax3Close;
	tif->tif_cleanup = Fax3Cleanup;

	return (1);
}
