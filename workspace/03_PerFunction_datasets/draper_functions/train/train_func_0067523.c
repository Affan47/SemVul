nroot(t)
	BTREE *t;
{
	PAGE *meta, *root;
	pgno_t npg;

	if ((meta = mpool_get(t->bt_mp, 0, 0)) != NULL) {
		mpool_put(t->bt_mp, meta, 0);
		return (RET_SUCCESS);
	}
	if (errno != EINVAL)
		return (RET_ERROR);
	errno = 0;

	if ((meta = mpool_new(t->bt_mp, &npg)) == NULL)
		return (RET_ERROR);

	if ((root = mpool_new(t->bt_mp, &npg)) == NULL)
		return (RET_ERROR);

	if (npg != P_ROOT)
		return (RET_ERROR);
	root->pgno = npg;
	root->prevpg = root->nextpg = P_INVALID;
	root->lower = BTDATAOFF;
	root->upper = t->bt_psize;
	root->flags = P_BLEAF;
	memset(meta, 0, t->bt_psize);
	mpool_put(t->bt_mp, meta, MPOOL_DIRTY);
	mpool_put(t->bt_mp, root, MPOOL_DIRTY);
	return (RET_SUCCESS);
}
