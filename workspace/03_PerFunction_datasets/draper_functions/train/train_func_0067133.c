M2TS_GetChannel(M2TSIn *m2ts, LPNETCHANNEL channel)
{
	u32 i;
	for (i=0; i<GF_M2TS_MAX_STREAMS; i++) {
		GF_M2TS_PES *pes = (GF_M2TS_PES *)m2ts->ts->ess[i];
		if (!pes || (pes->pid==pes->program->pmt_pid)) continue;
		if (pes->user == channel) return pes;
	}
	return NULL;
}
