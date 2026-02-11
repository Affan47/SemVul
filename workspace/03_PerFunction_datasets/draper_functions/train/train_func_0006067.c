__rec_fpipe(t, top)
	BTREE *t;
	recno_t top;
{
	DBT data;
	recno_t nrec;
	size_t len;
	int ch;
	u_char *p;

	if (t->bt_rdata.size < t->bt_reclen) {
		t->bt_rdata.data = t->bt_rdata.data == NULL ?
		    malloc(t->bt_reclen) :
		    realloc(t->bt_rdata.data, t->bt_reclen);
		if (t->bt_rdata.data == NULL)
			return (RET_ERROR);
		t->bt_rdata.size = t->bt_reclen;
	}
	data.data = t->bt_rdata.data;
	data.size = t->bt_reclen;

	for (nrec = t->bt_nrecs; nrec < top;) {
		len = t->bt_reclen;
		for (p = t->bt_rdata.data;; *p++ = ch)
			if ((ch = getc(t->bt_rfp)) == EOF || !--len) {
				if (ch != EOF)
					*p = ch;
				if (len != 0)
					memset(p, t->bt_bval, len);
				if (__rec_iput(t,
				    nrec, &data, 0) != RET_SUCCESS)
					return (RET_ERROR);
				++nrec;
				break;
			}
		if (ch == EOF)
			break;
	}
	if (nrec < top) {
		F_SET(t, R_EOF);
		return (RET_SPECIAL);
	}
	return (RET_SUCCESS);
}
