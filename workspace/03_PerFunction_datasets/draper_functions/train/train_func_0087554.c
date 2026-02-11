FreeEncoderAudio(IAudioEncoder* encoder)
{
    if (encoder)
    {
	const CodecInfo& info = encoder->GetCodecInfo();
	AVM_WRITE("codec keeper", 1, "FreeAudioEncoder() %s\n", info.GetName());
	delete encoder;
	plugin_close(info);
    }
}
