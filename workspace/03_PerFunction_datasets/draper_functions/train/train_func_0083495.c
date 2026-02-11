m2ts_export_check(GF_M2TS_Demuxer *ts, u32 evt_type, void *par)
{
	if (evt_type == GF_M2TS_EVT_PAT_REPEAT) ts->user = NULL;
	else if (evt_type == GF_M2TS_EVT_PAT_FOUND) ts->segment_switch = 1;
}
