addseq(struct unicode_list *up, unsigned int uc) {
	struct unicode_seq *us;
	struct unicode_seq *usl;
	struct unicode_list *ul = up->prev;

	usl = ul->seq;
	while (usl->next) usl = usl->next;
	us = xmalloc(sizeof(struct unicode_seq));
	us->uc = uc;
	us->prev = usl;
	us->next = NULL;
	usl->next = us;

}
