CreateEncoderAudio(fourcc_t compressor,
				  const WAVEFORMATEX* format)
{
    plugin_fill();

    avm::vector<CodecInfo*>::const_iterator it;
    for (it = audio_order.begin(); it != audio_order.end(); ++it)
    {
	const CodecInfo& ci = *(*it);
	if ((ci.direction & CodecInfo::Encode)
	    && ci.fourcc_array.find(compressor) != avm::vector<fourcc_t>::invalid)
	    if (IAudioEncoder* ae = CreateEncoderAudio(ci, format))
                return ae;
    }
    last_error.sprintf("No audio decoder for ID 0x%x", format->wFormatTag);
    return 0;
}
