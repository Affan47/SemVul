MP2TS_SendSLPacket(M2TSIn *m2ts, GF_M2TS_SL_PCK *pck)
{
	GF_SLHeader SLHeader, *slh = NULL;
	u32 SLHdrLen = 0;


	if (((GF_M2TS_ES*)pck->stream)->slcfg) {
		gf_sl_depacketize(((GF_M2TS_ES*)pck->stream)->slcfg, &SLHeader, pck->data, pck->data_len, &SLHdrLen);
		SLHeader.m2ts_version_number_plus_one = pck->version_number + 1;
		slh = &SLHeader;
	}
	gf_term_on_sl_packet(m2ts->service, pck->stream->user, pck->data+SLHdrLen, pck->data_len-SLHdrLen, slh, GF_OK);
}
