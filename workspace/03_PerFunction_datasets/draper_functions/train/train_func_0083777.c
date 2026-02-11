CTXLoad_AttachStream(GF_BaseDecoder *plug, GF_ESD *esd)
{
	const char *ext;
	GF_BitStream *bs;
	u32 size;
	CTXLoadPriv *priv = (CTXLoadPriv *)plug->privateStack;
	if (esd->decoderConfig->upstream) return GF_NOT_SUPPORTED;


	if (priv->ctx) {
		GF_StreamContext *sc;
		u32 i = 0;
		while ((sc = (GF_StreamContext *)gf_list_enum(priv->ctx->streams, &i))) {
			if (esd->ESID == sc->ESID) {
				priv->nb_streams++;
				return GF_OK;
			}
		}
		return GF_NON_COMPLIANT_BITSTREAM;
	}

	if (!esd->decoderConfig->decoderSpecificInfo)
		return GF_NON_COMPLIANT_BITSTREAM;
	bs = gf_bs_new(esd->decoderConfig->decoderSpecificInfo->data, esd->decoderConfig->decoderSpecificInfo->dataLength, GF_BITSTREAM_READ);
	priv->file_size = gf_bs_read_u32(bs);
	gf_bs_del(bs);
	size = esd->decoderConfig->decoderSpecificInfo->dataLength - sizeof(u32);
	priv->file_name = (char *) gf_malloc(sizeof(char)*(1 + size) );
	memcpy(priv->file_name, esd->decoderConfig->decoderSpecificInfo->data + sizeof(u32),  sizeof(char)*(esd->decoderConfig->decoderSpecificInfo->dataLength - sizeof(u32)) );
	priv->file_name[size] = 0;
	priv->nb_streams = 1;
	priv->load_flags = 0;
	priv->base_stream_id = esd->ESID;


	CTXLoad_Setup(plug);

	priv->progressive_support = 0;
	priv->sax_max_duration = 0;

	ext = strrchr(priv->file_name, '.');
	if (!ext) return GF_OK;

	ext++;
	if (!stricmp(ext, "xmt") || !stricmp(ext, "xmtz") || !stricmp(ext, "xmta")
		|| !stricmp(ext, "x3d") || !stricmp(ext, "x3dz")
	) {
		ext = gf_modules_get_option((GF_BaseInterface *)plug, "SAXLoader", "Progressive");
		priv->progressive_support = (ext && !stricmp(ext, "yes")) ? 1 : 0;
	}
	if (priv->progressive_support) {
		ext = gf_modules_get_option((GF_BaseInterface *)plug, "SAXLoader", "MaxDuration");
		if (ext) priv->sax_max_duration = atoi(ext);
	}
	return GF_OK;
}
