pk_gst_codec_free (PkGstCodecInfo *codec)
{
	if (codec->structure)
		gst_structure_free (codec->structure);
	g_free (codec->type_name);
	g_free (codec->codec_name);
	g_free (codec->app_name);
	g_free (codec->gstreamer_version);
}
