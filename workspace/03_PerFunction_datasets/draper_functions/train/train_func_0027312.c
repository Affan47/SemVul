dbsprline(DBPROCESS * dbproc, char *buffer, DBINT buf_len, DBCHAR line_char)
{
	TDSCOLUMN *colinfo;
	TDSRESULTINFO *resinfo;
	TDSSOCKET *tds;
	int i, col, len, collen, namlen;
	int c;

	tdsdump_log(TDS_DBG_FUNC, "dbsprline(%p, %s, %d, '%c')\n", dbproc, buffer, buf_len, line_char);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_NULP(buffer, "dbsprline", 2, FAIL);

	tds = dbproc->tds_socket;
	resinfo = tds->res_info;

	for (col = 0; col < resinfo->num_cols; col++) {
		colinfo = resinfo->columns[col];
		collen = _get_printable_size(colinfo);
		namlen = colinfo->column_namelen;
		len = collen > namlen ? collen : namlen;
		for (i = 0; i < len; i++) {
			if (buf_len < 1) {
				return FAIL;
			}
			*buffer++ = line_char;
			buf_len--;
		}
		if ((col + 1) < resinfo->num_cols) {
			i = 0;
			while ((c = dbstring_getchar(dbproc->dbopts[DBPRCOLSEP].param, i)) != -1) {
				if (buf_len < 1) {
					return FAIL;
				}
				*buffer++ = c;
				buf_len--;
				i++;
			}
		}
	}
	if (buf_len < 1) {
		return FAIL;
	}
	*buffer++ = '\0';
	return SUCCEED;
}
