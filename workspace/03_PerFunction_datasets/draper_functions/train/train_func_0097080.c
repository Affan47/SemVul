history_def_insert(history_t *h, TYPE(HistEvent) *ev, const Char *str)
{
	hentry_t *c;

	c = h_malloc(sizeof(*c));
	if (c == NULL)
		goto oomem;
	if ((c->ev.str = h_strdup(str)) == NULL) {
		h_free(c);
		goto oomem;
	}
	c->data = NULL;
	c->ev.num = ++h->eventid;
	c->next = h->list.next;
	c->prev = &h->list;
	h->list.next->prev = c;
	h->list.next = c;
	h->cur++;
	h->cursor = c;

	*ev = c->ev;
	return 0;
oomem:
	he_seterrev(ev, _HE_MALLOC_FAILED);
	return -1;
}
