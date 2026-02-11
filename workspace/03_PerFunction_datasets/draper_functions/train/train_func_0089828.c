M2TS_ConnectChannel(GF_InputService *plug, LPNETCHANNEL channel, const char *url, Bool upstream)
{
	u32 ES_ID;
	GF_Err e;
	M2TSIn *m2ts = plug->priv;

	e = GF_STREAM_NOT_FOUND;
	if (strstr(url, "ES_ID")) {
		sscanf(url, "ES_ID=%d", &ES_ID);


		if (gf_list_count(m2ts->ts->programs) == 1) {
			GF_M2TS_Program *prog = gf_list_get(m2ts->ts->programs, 0);
			if (prog->pmt_iod) {

				u32 i;
				for (i=0; i<GF_M2TS_MAX_STREAMS; i++) {
					GF_M2TS_PES *pes = (GF_M2TS_PES *)m2ts->ts->ess[i];
					if (!pes || (pes->pid==pes->program->pmt_pid)) continue;
					if ((pes->mpeg4_es_id == ES_ID)

						|| (!pes->mpeg4_es_id && (pes->pid == ES_ID))
					) {
						if (pes->user) {
							e = GF_SERVICE_ERROR;
							gf_term_on_connect(m2ts->service, channel, e);
							return e;
						} else {
							pes->user = channel;
							e = GF_OK;
							gf_term_on_connect(m2ts->service, channel, e);
							return e;
						}
					}
				}

				return e;
			}
		}


		if (ES_ID == 18) {
			e = GF_OK;
			m2ts->eit_channel = channel;
		} else if ((ES_ID<GF_M2TS_MAX_STREAMS) && m2ts->ts->ess[ES_ID]) {
			GF_M2TS_PES *pes = (GF_M2TS_PES *)m2ts->ts->ess[ES_ID];
			if (pes->user) {
				e = GF_SERVICE_ERROR;
			} else {
				pes->user = channel;
				e = GF_OK;
			}
		}
	}
	gf_term_on_connect(m2ts->service, channel, e);
	return e;
}
