CDB___db_prdbt(dbtp, checkprint, prefix, fp, is_recno)
	DBT *dbtp;
	int checkprint;
	const char *prefix;
	FILE *fp;
	int is_recno;
{
	static const char hex[] = "0123456789abcdef";
	db_recno_t recno;
	u_int32_t len;
	u_int8_t *p;


	if (prefix != NULL && fprintf(fp, "%s", prefix) != (int)strlen(prefix))
		return (EIO);
	if (is_recno) {


		CDB___ua_memcpy(&recno, dbtp->data, sizeof(recno));
		if (fprintf(fp, "%lu", (u_long)recno) == 0)
			return (EIO);
	} else if (checkprint) {
		for (len = dbtp->size, p = dbtp->data; len--; ++p)
			if (isprint(*p)) {
				if (*p == '\\' && fprintf(fp, "\\") != 1)
					return (EIO);
				if (fprintf(fp, "%c", *p) != 1)
					return (EIO);
			} else
				if (fprintf(fp, "\\%c%c",
				    hex[(u_int8_t)(*p & 0xf0) >> 4],
				    hex[*p & 0x0f]) != 3)
					return (EIO);
	} else
		for (len = dbtp->size, p = dbtp->data; len--; ++p)
			if (fprintf(fp, "%c%c",
			    hex[(u_int8_t)(*p & 0xf0) >> 4],
			    hex[*p & 0x0f]) != 2)
				return (EIO);

	return (fprintf(fp, "\n") == 1 ? 0 : EIO);
}
