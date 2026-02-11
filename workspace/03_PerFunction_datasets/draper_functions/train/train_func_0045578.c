MP2TS_SendPacket(M2TSIn *m2ts, GF_M2TS_PES_PCK *pck)
{
	GF_SLHeader slh;


	if (! pck->stream->program->first_dts) return;
	if (!pck->stream->user) return;

	memset(&slh, 0, sizeof(GF_SLHeader));
	slh.accessUnitStartFlag = (pck->flags & GF_M2TS_PES_PCK_AU_START) ? 1 : 0;
	if (slh.accessUnitStartFlag) {
#if 0
		slh.OCRflag = 1;
		slh.m2ts_pcr = 1;
		slh.objectClockReference = pck->stream->program->last_pcr_value;
#else
		slh.OCRflag = 0;
#endif
		slh.compositionTimeStampFlag = 1;
		slh.compositionTimeStamp = pck->PTS;
		if (pck->DTS) {
			slh.decodingTimeStampFlag = 1;
			slh.decodingTimeStamp = pck->DTS;
		}
		slh.randomAccessPointFlag = (pck->flags & GF_M2TS_PES_PCK_RAP) ? 1 : 0;
	}
	gf_term_on_sl_packet(m2ts->service, pck->stream->user, pck->data, pck->data_len, &slh, GF_OK);
}
