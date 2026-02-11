__db_pglist_swap(size, list)
	u_int32_t size;
	void *list;
{
	db_pglist_t *lp;
	u_int32_t nelem;

	nelem = size / sizeof(db_pglist_t);

	lp = (db_pglist_t *)list;
	while (nelem-- > 0) {
		P_32_SWAP(&lp->pgno);
		P_32_SWAP(&lp->lsn.file);
		P_32_SWAP(&lp->lsn.offset);
		lp++;
	}
}
