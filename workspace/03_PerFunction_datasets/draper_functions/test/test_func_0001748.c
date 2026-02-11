history_def_delete(history_t *h,
		   TYPE(HistEvent) *ev __attribute__((__unused__)), hentry_t *hp)
{
	HistEventPrivate *evp = (void *)&hp->ev;
	if (hp == &h->list)
		abort();
	if (h->cursor == hp) {
		h->cursor = hp->prev;
		if (h->cursor == &h->list)
			h->cursor = hp->next;
	}
	hp->prev->next = hp->next;
	hp->next->prev = hp->prev;
	h_free(evp->str);
	h_free(hp);
	h->cur--;
}
