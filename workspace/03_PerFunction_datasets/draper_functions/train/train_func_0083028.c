sdp_seq_append(sdp_data_t *seq, sdp_data_t *d)
{
	if (seq) {
		sdp_data_t *p;
		for (p = seq; p->next; p = p->next);
		p->next = d;
	} else
		seq = d;
	d->next = NULL;
	return seq;
}
