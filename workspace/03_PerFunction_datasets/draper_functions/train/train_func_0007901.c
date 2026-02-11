ecpg_build_compat_sqlda(int line, PGresult *res, int row, enum COMPAT_MODE compat)
{
	struct sqlda_compat *sqlda;
	struct sqlvar_compat *sqlvar;
	char	   *fname;
	long		size;
	int			sqld;
	int			i;

	size = sqlda_compat_total_size(res, row, compat);
	sqlda = (struct sqlda_compat *) ecpg_alloc(size, line);
	if (!sqlda)
		return NULL;

	memset(sqlda, 0, size);
	sqlvar = (struct sqlvar_compat *) (sqlda + 1);
	sqld = PQnfields(res);
	fname = (char *) (sqlvar + sqld);

	sqlda->sqld = sqld;
	ecpg_log("ecpg_build_compat_sqlda on line %d sqld = %d\n", line, sqld);
	sqlda->desc_occ = size;
	sqlda->sqlvar = sqlvar;

	for (i = 0; i < sqlda->sqld; i++)
	{
		sqlda->sqlvar[i].sqltype = sqlda_dynamic_type(PQftype(res, i), compat);
		strcpy(fname, PQfname(res, i));
		sqlda->sqlvar[i].sqlname = fname;
		fname += strlen(sqlda->sqlvar[i].sqlname) + 1;


		sqlda->sqlvar[i].sqlxid = PQftype(res, i);
		sqlda->sqlvar[i].sqltypelen = PQfsize(res, i);
	}

	return sqlda;
}
