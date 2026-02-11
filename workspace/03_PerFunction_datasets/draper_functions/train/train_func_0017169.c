completeSetup(AFfilesetup setup)
{
	TrackSetup	*track;

	if (setup->trackSet && setup->trackCount != 1)
	{
		_af_error(AF_BAD_NUMTRACKS, "NIST SPHERE file must have 1 track");
		return AF_NULL_FILESETUP;
	}

	track = &setup->tracks[0];

	if (track->sampleFormatSet)
	{

		if (track->f.sampleFormat == AF_SAMPFMT_TWOSCOMP &&
			(track->f.sampleWidth < 1 || track->f.sampleWidth > 16))
		{
			_af_error(AF_BAD_WIDTH,
				"invalid sample width %d bits for NIST SPHERE format",
				track->f.sampleWidth);
			return AF_NULL_FILESETUP;
		}
		else if (track->f.sampleFormat == AF_SAMPFMT_UNSIGNED)
		{
			_af_error(AF_BAD_SAMPFMT,
				"NIST SPHERE format does not support unsigned data");
			return AF_NULL_FILESETUP;
		}
		else if (track->f.sampleFormat == AF_SAMPFMT_FLOAT ||
			track->f.sampleFormat == AF_SAMPFMT_DOUBLE)
		{
			_af_error(AF_BAD_SAMPFMT,
				"NIST SPHERE format does not support floating-point data");
			return AF_NULL_FILESETUP;
		}
	}

	if (track->rateSet && track->f.sampleRate <= 0.0)
	{
		_af_error(AF_BAD_RATE,
			"invalid sample rate %.30g for NIST SPHERE file",
			track->f.sampleRate);
		return AF_NULL_FILESETUP;
	}

	if (track->compressionSet && track->f.compressionType != AF_COMPRESSION_NONE &&
		track->f.compressionType != AF_COMPRESSION_G711_ULAW &&
		track->f.compressionType != AF_COMPRESSION_G711_ALAW)
	{
		_af_error(AF_BAD_NOT_IMPLEMENTED,
			"NIST SPHERE format supports only G.711 u-law or A-law compression");
		return AF_NULL_FILESETUP;
	}

	if (track->aesDataSet)
	{
		_af_error(AF_BAD_FILESETUP, "NIST SPHERE file cannot have AES data");
		return AF_NULL_FILESETUP;
	}

	if (track->markersSet && track->markerCount != 0)
	{
		_af_error(AF_BAD_NUMMARKS, "NIST SPHERE format does not support markers");
		return AF_NULL_FILESETUP;
	}

	if (setup->instrumentSet && setup->instrumentCount != 0)
	{
		_af_error(AF_BAD_NUMINSTS, "NIST SPHERE format does not support instruments");
		return AF_NULL_FILESETUP;
	}


	if (setup->miscellaneousSet && setup->miscellaneousCount != 0)
	{
		_af_error(AF_BAD_NOT_IMPLEMENTED, "NIST SPHERE format does not currently support miscellaneous chunks");
		return AF_NULL_FILESETUP;
	}

	return _af_filesetup_copy(setup, &nistDefaultFileSetup, true);
}
