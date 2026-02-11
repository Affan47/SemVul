FFDEC_GetCodecName(GF_BaseDecoder *dec)
{
	FFDec *ffd;
	if (!dec)
		return NULL;
	ffd = dec->privateStack;
	if (ffd && ffd->base_codec) {
		sprintf(ffd->szCodec, "FFMPEG %s", ffd->base_codec->name ? ffd->base_codec->name : "unknown");
		return ffd->szCodec;
	}
	return NULL;
}
