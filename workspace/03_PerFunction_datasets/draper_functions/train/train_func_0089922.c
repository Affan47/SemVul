__ram_add(dbc, recnop, data, flags, bi_flags)
	DBC *dbc;
	db_recno_t *recnop;
	DBT *data;
	u_int32_t flags, bi_flags;
{
	BTREE_CURSOR *cp;
	int exact, ret, stack, t_ret;

	cp = (BTREE_CURSOR *)dbc->internal;

retry:
	if ((ret = __bam_rsearch(dbc, recnop,
	    SR_INSERT | (flags == DB_APPEND ? SR_APPEND : 0), 1, &exact)) != 0)
		return (ret);
	stack = 1;


	STACK_TO_CURSOR(cp, ret);
	if (ret != 0)
		goto err;

	if (exact && flags == DB_NOOVERWRITE && !CD_ISSET(cp) &&
	    !B_DISSET(GET_BKEYDATA(dbc->dbp, cp->page, cp->indx)->type)) {
		ret = DB_KEYEXIST;
		goto err;
	}


	if (flags == DB_APPEND && dbc->dbp->db_append_recno != NULL &&
	    (ret = dbc->dbp->db_append_recno(dbc->dbp, data, *recnop)) != 0)
		goto err;


	switch (ret = __bam_iitem(dbc,
	    NULL, data, exact ? DB_CURRENT : DB_BEFORE, bi_flags)) {
	case 0:


		break;
	case DB_NEEDSPLIT:

		(void)__bam_stkrel(dbc, STK_CLRDBC);
		stack = 0;

		if ((ret = __bam_split(dbc, recnop, NULL)) != 0)
			goto err;

		goto retry;

	default:
		goto err;
	}

err:	if (stack && (t_ret = __bam_stkrel(dbc, STK_CLRDBC)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
