copy_transponder(struct transponder *d, struct transponder *s, int isOverride)
{
	d->network_id = s->network_id;
	d->original_network_id = s->original_network_id;
	d->transport_stream_id = s->transport_stream_id;
	d->frequency = s->frequency;
	d->symbol_rate = s->symbol_rate;
	d->inversion = s->inversion;
	if(isOverride || d->rolloff == ROLLOFF_AUTO) {
		d->rolloff = s->rolloff;
	}
	if(isOverride || d->fec == FEC_AUTO) {
		d->fec = s->fec;
	}
	if(isOverride || d->fecHP == FEC_AUTO) {
		d->fecHP = s->fecHP;
	}
	if(isOverride || d->fecLP == FEC_AUTO) {
		d->fecLP = s->fecLP;
	}
	if(isOverride || d->modulation == QAM_AUTO) {
		d->modulation = s->modulation;
	}
	if(isOverride || d->bandwidth == BANDWIDTH_AUTO) {
		d->bandwidth = s->bandwidth;
	}
	if(isOverride || d->hierarchy == HIERARCHY_AUTO) {
		d->hierarchy = s->hierarchy;
	}
	if(isOverride || d->guard_interval == GUARD_INTERVAL_AUTO) {
		d->guard_interval = s->guard_interval;
	}
	if(isOverride || d->transmission_mode == TRANSMISSION_MODE_AUTO) {
		d->transmission_mode = s->transmission_mode;
	}
	d->polarisation = s->polarisation;
	d->orbital_pos = s->orbital_pos;
	d->delivery_system = s->delivery_system;
	d->we_flag = s->we_flag;
	d->scan_done = s->scan_done;
	d->last_tuning_failed = s->last_tuning_failed;
	d->other_frequency_flag = s->other_frequency_flag;
	d->n_other_f = s->n_other_f;
	if (d->n_other_f) {
		d->other_f = calloc(d->n_other_f, sizeof(uint32_t));
		memcpy(d->other_f, s->other_f, d->n_other_f * sizeof(uint32_t));
	}
	else
		d->other_f = NULL;
}
