LoadInterface(u32 InterfaceType)
{
	if (InterfaceType == GF_MEDIA_DECODER_INTERFACE) return FFDEC_Load();
#ifndef DISABLE_FFMPEG_DEMUX
	if (InterfaceType == GF_NET_CLIENT_INTERFACE) return New_FFMPEG_Demux();
#endif
	return NULL;
}
