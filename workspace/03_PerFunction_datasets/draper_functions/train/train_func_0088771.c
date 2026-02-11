__rec_search(t, recno, op)
	BTREE *t;
	recno_t recno;
	enum SRCHOP op;
{
	register indx_t index;
	register PAGE *h;
	EPGNO *parent;
	RINTERNAL *r;
	pgno_t pg;
	indx_t top;
	recno_t total;
	int sverrno;

	BT_CLR(t);
	for (pg = P_ROOT, total = 0;;) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			goto err;
		if (h->flags & P_RLEAF) {
			t->bt_cur.page = h;
			t->bt_cur.index = recno - total;
			return (&t->bt_cur);
		}
		for (index = 0, top = NEXTINDEX(h);;) {
			r = GETRINTERNAL(h, index);
			if (++index == top || total + r->nrecs > recno)
				break;
			total += r->nrecs;
		}

		BT_PUSH(t, pg, index - 1);

		pg = r->pgno;
		switch (op) {
		case SDELETE:
			--GETRINTERNAL(h, (index - 1))->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SINSERT:
			++GETRINTERNAL(h, (index - 1))->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SEARCH:
			mpool_put(t->bt_mp, h, 0);
			break;
		}

	}

err:	sverrno = errno;
	if (op != SEARCH)
		while  ((parent = BT_POP(t)) != NULL) {
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
				break;
			if (op == SINSERT)
				--GETRINTERNAL(h, parent->index)->nrecs;
			else
				++GETRINTERNAL(h, parent->index)->nrecs;
                        mpool_put(t->bt_mp, h, MPOOL_DIRTY);
                }
	errno = sverrno;
	return (NULL);
}
