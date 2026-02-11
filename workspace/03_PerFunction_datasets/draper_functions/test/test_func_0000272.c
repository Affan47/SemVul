M2TS_DisconnectChannel(GF_InputService *plug, LPNETCHANNEL channel)
{
	M2TSIn *m2ts = plug->priv;
	GF_Err e = GF_STREAM_NOT_FOUND;
	GF_M2TS_PES *pes = M2TS_GetChannel(m2ts, channel);
	if (pes) {
		pes->user = NULL;
		e = GF_OK;
	}
	gf_term_on_disconnect(m2ts->service, channel, e);
	return GF_OK;
}
