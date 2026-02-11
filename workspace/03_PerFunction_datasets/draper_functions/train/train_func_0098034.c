OGG_CanHandleStream(GF_BaseDecoder *dec, u32 StreamType, GF_ESD *esd, u8 PL)
{

	if (StreamType == GF_STREAM_VISUAL) {
		char *dsi;

		if (!esd) return GF_CODEC_STREAM_TYPE_SUPPORTED;
		dsi = esd->decoderConfig->decoderSpecificInfo ? esd->decoderConfig->decoderSpecificInfo->data : NULL;

		switch (esd->decoderConfig->objectTypeIndication) {
#ifdef GPAC_HAS_THEORA
		case GPAC_OTI_MEDIA_OGG:
			if (dsi && (esd->decoderConfig->decoderSpecificInfo->dataLength>=9)  && !strncmp((char *) &dsi[3], "theora", 6)) {
				if (NewTheoraDecoder(dec)) return GF_CODEC_SUPPORTED;
			}
			return GF_CODEC_NOT_SUPPORTED;
#endif
		default:
			return GF_CODEC_NOT_SUPPORTED;
		}
	}

	if (StreamType == GF_STREAM_AUDIO) {
		char *dsi;

		if (!esd) return GF_CODEC_STREAM_TYPE_SUPPORTED;
		dsi = esd->decoderConfig->decoderSpecificInfo ? esd->decoderConfig->decoderSpecificInfo->data : NULL;

		switch (esd->decoderConfig->objectTypeIndication) {
#ifdef GPAC_HAS_VORBIS
		case GPAC_OTI_MEDIA_OGG:
			if (dsi && (esd->decoderConfig->decoderSpecificInfo->dataLength>=9)  && !strncmp((char *) &dsi[3], "vorbis", 6)) {
				if (NewVorbisDecoder(dec)) return GF_CODEC_SUPPORTED;
			}
			return GF_CODEC_NOT_SUPPORTED;
#endif
		default:
			return GF_CODEC_NOT_SUPPORTED;
		}
	}
	return GF_CODEC_NOT_SUPPORTED;
}
