BIFS_DetachStream(GF_BaseDecoder *plug, u16 ES_ID)
{
	GF_Err e;
	BIFSPriv *priv = (BIFSPriv *)plug->privateStack;
	e = gf_bifs_decoder_remove_stream(priv->codec, ES_ID);
	if (e) return e;
	priv->nb_streams--;
	return GF_OK;
}
