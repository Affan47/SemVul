gf_term_forward_event(GF_Terminal *term, GF_Event *evt, Bool consumed, Bool forward_only)
{
	if (!term) return 0;

	if (term->event_filters) {
		GF_TermEventFilter *ef;
		u32 i=0;

		gf_mx_p(term->evt_mx);
		term->in_event_filter ++;
		gf_mx_v(term->evt_mx);
		while ((ef=gf_list_enum(term->event_filters, &i))) {
			if (ef->on_event(ef->udta, evt, consumed)) {
				term->in_event_filter --;
				return 1;
			}
		}
		term->in_event_filter --;
	}

	if (!forward_only && !consumed && term->user->EventProc)
		return term->user->EventProc(term->user->opaque, evt);

	return 0;
}
