TSDemux_CloseDemux(GF_M2TS_Demuxer *ts)
{
	GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[TSDemux] Destroying demuxer\n"));
	if (ts->th) {
		if (ts->run_state == 1) {
			ts->run_state = 0;
			while (ts->run_state!=2) gf_sleep(0);
		}
		gf_th_del(ts->th);
		ts->th = NULL;
	}

	if (ts->file) fclose(ts->file);
	ts->file = NULL;
	ts->ts_data_chunk = NULL;

	return GF_OK;
}
