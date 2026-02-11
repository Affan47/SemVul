history_def_next(void *p, TYPE(HistEvent) *ev)
{
	history_t *h = (history_t *) p;

	if (h->cursor == &h->list) {
		he_seterrev(ev, _HE_EMPTY_LIST);
		return -1;
	}

	if (h->cursor->next == &h->list) {
		he_seterrev(ev, _HE_END_REACHED);
		return -1;
	}

        h->cursor = h->cursor->next;
        *ev = h->cursor->ev;

	return 0;
}
