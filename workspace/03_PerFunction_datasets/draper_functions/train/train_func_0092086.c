isor_reset_reader(ISOMChannel *ch)
{
	memset(&ch->current_slh, 0, sizeof(GF_SLHeader));
	ch->last_state = GF_OK;
	if (ch->sample) gf_isom_sample_del(&ch->sample);
	ch->sample = NULL;
	ch->sample_num = 0;
	ch->speed = 1.0;
	ch->start = ch->end = 0;
	ch->to_init = 1;
	ch->is_playing = 0;
}
