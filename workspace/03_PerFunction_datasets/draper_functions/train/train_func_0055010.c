gf_es_start(GF_Channel *ch)
{
	if (!ch) return GF_BAD_PARAM;

	switch (ch->es_state) {
	case GF_ESM_ES_UNAVAILABLE:
	case GF_ESM_ES_SETUP:
		return GF_BAD_PARAM;


	case GF_ESM_ES_RUNNING:
		return GF_OK;
	default:
		break;
	}
	GF_LOG(GF_LOG_INFO, GF_LOG_SYNC, ("[SyncLayer] Starting ES %d\n", ch->esd->ESID));


	if (gf_es_owns_clock(ch) && !ch->clock->no_time_ctrl)
		gf_clock_reset(ch->clock);


	Channel_Reset(ch, 1);

	if (ch->is_pulling && !ch->AU_buffer_pull) ch->AU_buffer_pull = gf_db_unit_new();


	if ((ch->esd->decoderConfig->streamType != GF_STREAM_INTERACT) || ch->esd->URLString) {


			ch_buffer_on(ch);
	}
	ch->last_au_time = gf_term_get_time(ch->odm->term);
	ch->es_state = GF_ESM_ES_RUNNING;

	ch->resync_drift = 0;
	if (ch->clock->clockID==ch->esd->ESID) {
		const char *opt = gf_cfg_get_key(ch->clock->term->user->config, "Systems", "ResyncLateClock");
		if (opt) ch->resync_drift = atoi(opt);
	}
	return GF_OK;
}
