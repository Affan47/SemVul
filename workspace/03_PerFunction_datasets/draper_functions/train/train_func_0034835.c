CreateEncoderAudio(const CodecInfo& ci, const WAVEFORMATEX* fmt)
{
    if (!(ci.direction & CodecInfo::Encode))
	return 0;
    if (audio_codecs.find(ci) == avm::vector<CodecInfo>::invalid)
    {
	AVM_WRITE("codec keeper", "Failed to find this CodecInfo in list\n");
	return 0;
    }

    codec_plugin_t* plugin = plugin_open(ci);
    if (plugin && plugin->audio_encoder)
    {
	if (IAudioEncoder* ae = plugin->audio_encoder(ci, ci.fourcc, fmt))
	    return ae;
	plugin_get_error(plugin);
    }
    plugin_close(ci);

    return 0;
}
