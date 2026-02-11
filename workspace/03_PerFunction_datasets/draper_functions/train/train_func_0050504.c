gf_es_on_eos(GF_Channel *ch)
{
	if (!ch || ch->IsEndOfStream) return;
	ch->IsEndOfStream = 1;


	ch_buffer_off(ch);
	if (ch->len)
		Channel_DispatchAU(ch, 0);

	gf_odm_on_eos(ch->odm, ch);
}
