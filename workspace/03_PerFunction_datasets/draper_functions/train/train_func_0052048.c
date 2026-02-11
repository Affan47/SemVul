history_getsize(TYPE(History) *h, TYPE(HistEvent) *ev)
{
	if (h->h_next != history_def_next) {
		he_seterrev(ev, _HE_NOT_ALLOWED);
		return -1;
	}
	ev->num = history_def_getsize(h->h_ref);
	if (ev->num < -1) {
		he_seterrev(ev, _HE_SIZE_NEGATIVE);
		return -1;
	}
	return 0;
}
