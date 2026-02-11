__db_vrfy_freelist(dbp, vdp, meta, flags)
	DB *dbp;
	VRFY_DBINFO *vdp;
	db_pgno_t meta;
	u_int32_t flags;
{
	DB *pgset;
	ENV *env;
	VRFY_PAGEINFO *pip;
	db_pgno_t cur_pgno, next_pgno;
	int p, ret, t_ret;

	env = dbp->env;
	pgset = vdp->pgset;
	DB_ASSERT(env, pgset != NULL);

	if ((ret = __db_vrfy_getpageinfo(vdp, meta, &pip)) != 0)
		return (ret);
	for (next_pgno = pip->free;
	    next_pgno != PGNO_INVALID; next_pgno = pip->next_pgno) {
		cur_pgno = pip->pgno;
		if ((t_ret = __db_vrfy_putpageinfo(env, vdp, pip)) != 0)
			return (t_ret);


		if (!IS_VALID_PGNO(next_pgno)) {
			EPRINT((env, DB_STR_A("0553",
			    "Page %lu: invalid next_pgno %lu on free list page",
			    "%lu %lu"), (u_long)cur_pgno, (u_long)next_pgno));
			return (DB_VERIFY_BAD);
		}

		if (next_pgno > vdp->last_pgno) {
			EPRINT((env, DB_STR_A("0713",
			 "Page %lu: page %lu on free list beyond last_pgno %lu",
			    "%lu %lu %lu"), (u_long)cur_pgno,
			    (u_long)next_pgno, (u_long)vdp->last_pgno));
			ret = DB_VERIFY_BAD;
		}

		if ((t_ret = __db_vrfy_pgset_get(pgset,
		    vdp->thread_info, vdp->txn, next_pgno, &p)) != 0)
			return (t_ret);
		if (p != 0) {
			EPRINT((env, DB_STR_A("0554",
		    "Page %lu: page %lu encountered a second time on free list",
			    "%lu %lu"), (u_long)cur_pgno, (u_long)next_pgno));
			return (DB_VERIFY_BAD);
		}
		if ((t_ret = __db_vrfy_pgset_inc(pgset,
		    vdp->thread_info, vdp->txn, next_pgno)) != 0)
			return (t_ret);

		if ((t_ret = __db_vrfy_getpageinfo(vdp, next_pgno, &pip)) != 0)
			return (t_ret);

		if (pip->type != P_INVALID) {
			EPRINT((env, DB_STR_A("0555",
			    "Page %lu: non-invalid page %lu on free list",
			    "%lu %lu"), (u_long)cur_pgno, (u_long)next_pgno));
			ret = DB_VERIFY_BAD;
			break;
		}
	}

	if ((t_ret = __db_vrfy_putpageinfo(env, vdp, pip)) != 0 && ret == 0)
		ret = t_ret;
	return (ret);
}
