completeSetup(AFfilesetup setup)
{
	if (setup->trackSet && setup->trackCount != 1)
	{
		_af_error(AF_BAD_NUMTRACKS, "CAF file must have 1 track");
		return AF_NULL_FILESETUP;
	}

	TrackSetup *track = &setup->tracks[0];

	if (track->sampleFormatSet)
	{
		if (track->f.isUnsigned())
		{
			_af_error(AF_BAD_FILEFMT, "CAF format does not support unsigned data");
			return AF_NULL_FILESETUP;
		}
	}
	else
		_af_set_sample_format(&track->f, AF_SAMPFMT_TWOSCOMP,
			track->f.sampleWidth);

	if (track->f.isSigned() && (track->f.sampleWidth < 1 || track->f.sampleWidth > 32))
	{
		_af_error(AF_BAD_WIDTH,
			"invalid sample width %d for CAF file (must be 1-32)",
			track->f.sampleWidth);
		return AF_NULL_FILESETUP;
	}

	if (!track->byteOrderSet)
		track->f.byteOrder = _AF_BYTEORDER_NATIVE;

	if (track->f.compressionType != AF_COMPRESSION_NONE &&
		track->f.compressionType != AF_COMPRESSION_G711_ULAW &&
		track->f.compressionType != AF_COMPRESSION_G711_ALAW &&
		track->f.compressionType != AF_COMPRESSION_IMA &&
		track->f.compressionType != AF_COMPRESSION_ALAC)
	{
		_af_error(AF_BAD_COMPTYPE,
			"compression format %d not supported in CAF file",
			track->f.compressionType);
		return AF_NULL_FILESETUP;
	}

	if (track->markersSet && track->markerCount)
	{
		_af_error(AF_BAD_NOT_IMPLEMENTED, "CAF does not yet support markers");
		return AF_NULL_FILESETUP;
	}

	if (track->aesDataSet)
	{
		_af_error(AF_BAD_FILESETUP, "CAF does not support AES data");
		return AF_NULL_FILESETUP;
	}

	return _af_filesetup_copy(setup, &cafDefaultFileSetup, true);
}
