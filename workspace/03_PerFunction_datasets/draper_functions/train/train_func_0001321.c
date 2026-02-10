insert_clef(struct SYMBOL *s,
			int clef_type)
{
	struct VOICE_S *p_voice;
	struct SYMBOL *new_s;


	if (s->type == BAR && s->prev != 0 && s->prev->type == BAR

			)
		s = s->prev;


	p_voice = &voice_tb[s->voice];
	if ((p_voice->last_sym = s->prev) == 0)
		p_voice->sym = 0;
	p_voice->time = s->time;
	new_s = sym_add(p_voice, CLEF);
	new_s->next = s;
	s->prev = new_s;

	new_s->as.u.clef.type = clef_type;
	new_s->as.u.clef.line = clef_type == TREBLE ? 2 : 4;
	new_s->staff = s->staff;
	new_s->u = 1;
	new_s->sflags &= ~S_SECOND;


	while (!(s->sflags & S_SEQST))
		s = s->ts_prev;
	if (s->type == STAVES) {
		s = s->ts_next;
		s->sflags |= S_SEQST;
	} else if (s->ts_prev == 0 || s->ts_prev->type != CLEF) {
		new_s->sflags |= S_SEQST;
	}
	if ((new_s->ts_prev = s->ts_prev) != 0)
		new_s->ts_prev->ts_next = new_s;
	else
		tsfirst = new_s;
	new_s->ts_next = s;
	s->ts_prev = new_s;
}
