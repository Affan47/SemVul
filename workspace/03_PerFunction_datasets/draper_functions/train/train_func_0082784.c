__bt_snext(t, h, key, exactp)
	BTREE *t;
	PAGE *h;
	const DBT *key;
	int *exactp;
{
	BINTERNAL *bi;
	EPG e;
	EPGNO *parent;
	indx_t idx = 0;
	db_pgno_t pgno;
	int level;


	if ((e.page = mpool_get(t->bt_mp, h->nextpg, 0)) == NULL)
		return (0);
	e.index = 0;
	if (__bt_cmp(t, key, &e) != 0) {
		mpool_put(t->bt_mp, e.page, 0);
		return (0);
	}
	mpool_put(t->bt_mp, h, 0);
	t->bt_cur = e;
	*exactp = 1;


	for (level = 0; (parent = BT_POP(t)) != NULL; ++level) {

		if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
			return (0);


		if (parent->index != NEXTINDEX(h) - 1) {
			idx = parent->index + 1;
			BT_PUSH(t, h->pgno, idx);
			break;
		}
		mpool_put(t->bt_mp, h, 0);
	}


	while (level--) {

		bi = GETBINTERNAL(h, idx);
		pgno = bi->pgno;
		BT_PUSH(t, pgno, 0);


		mpool_put(t->bt_mp, h, 0);


		if ((h = mpool_get(t->bt_mp, pgno, 0)) == NULL)
			return (0);
		idx = 0;
	}
	mpool_put(t->bt_mp, h, 0);
	return (1);
}
