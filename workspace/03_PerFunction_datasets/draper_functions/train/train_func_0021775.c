MP2TS_SetupProgram(M2TSIn *m2ts, GF_M2TS_Program *prog, Bool regenerate_scene, Bool no_declare)
{
	u32 i, count;

	count = gf_list_count(prog->streams);
#ifdef GPAC_HAS_LINUX_DVB
	if (m2ts->ts->tuner) {
		Bool found = 0;
		for (i=0; i<count; i++) {
			GF_M2TS_PES *pes = gf_list_get(prog->streams, i);
			if (pes->pid==m2ts->ts->tuner->vpid) found = 1;
			else if (pes->pid==m2ts->ts->tuner->apid) found = 1;
		}
		if (!found) return;
	}
#endif


	if (m2ts->ts->file || m2ts->ts->dnload) m2ts->ts->file_regulate = 1;

	for (i=0; i<count; i++) {
		GF_M2TS_ES *es = gf_list_get(prog->streams, i);
		if (es->pid==prog->pmt_pid) continue;

		if (!es->user)
			gf_m2ts_set_pes_framing((GF_M2TS_PES *)es, GF_M2TS_PES_FRAMING_SKIP);

		if (!prog->pmt_iod && !no_declare) {
			MP2TS_DeclareStream(m2ts, (GF_M2TS_PES *)es, NULL, 0);
		}


	}


	if (!prog->pmt_iod && regenerate_scene)
		gf_term_add_media(m2ts->service, NULL, 0);
}
