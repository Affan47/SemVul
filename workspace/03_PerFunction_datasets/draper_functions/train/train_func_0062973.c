__bt_seq(dbp, key, data, flags)
	const DB *dbp;
	DBT *key, *data;
	u_int flags;
{
	BTREE *t;
	EPG e;
	int status;

	t = dbp->internal;


	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}


	switch (flags) {
	case R_NEXT:
	case R_PREV:
		if (F_ISSET(&t->bt_cursor, CURS_INIT)) {
			status = __bt_seqadv(t, &e, flags);
			break;
		}

	case R_FIRST:
	case R_LAST:
	case R_CURSOR:
		status = __bt_seqset(t, &e, key, flags);
		break;
	default:
		errno = EINVAL;
		return (RET_ERROR);
	}

	if (status == RET_SUCCESS) {
		__bt_setcur(t, e.page->pgno, e.index);

		status =
		    __bt_ret(t, &e, key, &t->bt_rkey, data, &t->bt_rdata, 0);


		if (F_ISSET(t, B_DB_LOCK))
			mpool_put(t->bt_mp, e.page, 0);
		else
			t->bt_pinned = e.page;
	}
	return (status);
}
