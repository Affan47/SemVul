LSR_AttachStream(GF_BaseDecoder *plug, GF_ESD *esd)
{
	LSRPriv *priv = (LSRPriv *)plug->privateStack;
	GF_Err e;
	if (esd->decoderConfig->upstream) return GF_NOT_SUPPORTED;
	e = gf_laser_decoder_configure_stream(priv->codec, esd->ESID, esd->decoderConfig->decoderSpecificInfo->data, esd->decoderConfig->decoderSpecificInfo->dataLength);
	if (!e) priv->nb_streams++;
	return e;
}
