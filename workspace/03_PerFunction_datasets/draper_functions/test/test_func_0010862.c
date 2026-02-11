xmms_apefile_init (xmms_xform_t *xform)
{
	xmms_apefile_data_t *data;
	guchar decoder_config[6];

	data = g_new0 (xmms_apefile_data_t, 1);
	data->seektable = NULL;
	data->buffer = NULL;

	xmms_xform_private_data_set (xform, data);

	if (!xmms_apefile_init_demuxer (xform)) {
		xmms_log_error ("Couldn't initialize the demuxer, please check log");
		return FALSE;
	}


	if (!xmms_apefile_read_tags (xform)) {
		XMMS_DBG ("Couldn't read tags from the file");
	}

	xmms_xform_metadata_set_int (xform,
	                             XMMS_MEDIALIB_ENTRY_PROPERTY_DURATION,
	                             data->totalsamples / data->samplerate * 1000);

	xmms_xform_auxdata_set_int (xform,
	                            "samplebits",
	                            data->samplebits);

	set_le16 (decoder_config + 0, data->fileversion);
	set_le16 (decoder_config + 2, data->compressiontype);
	set_le16 (decoder_config + 4, data->formatflags);
	xmms_xform_auxdata_set_bin (xform,
	                            "decoder_config",
	                            decoder_config,
	                            sizeof (decoder_config));

	xmms_xform_outdata_type_add (xform,
	                             XMMS_STREAM_TYPE_MIMETYPE,
	                             "audio/x-ffmpeg-ape",
	                             XMMS_STREAM_TYPE_FMT_CHANNELS,
	                             data->channels,
	                             XMMS_STREAM_TYPE_FMT_SAMPLERATE,
	                             data->samplerate,
	                             XMMS_STREAM_TYPE_END);

	return TRUE;
}
