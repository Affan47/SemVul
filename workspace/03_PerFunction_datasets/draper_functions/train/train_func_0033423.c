dbsprhead(DBPROCESS * dbproc, char *buffer, DBINT buf_len)
{
	TDSCOLUMN *colinfo;
	TDSRESULTINFO *resinfo;
	TDSSOCKET *tds;
	int i, col, collen, namlen;
	int padlen;
	int c;

	tdsdump_log(TDS_DBG_FUNC, "dbsprhead(%p, %s, %d)\n", dbproc, buffer, buf_len);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_NULP(buffer, "dbsprhead", 2, FAIL);

	tds = dbproc->tds_socket;
	resinfo = tds->res_info;

	for (col = 0; col < resinfo->num_cols; col++) {
		colinfo = resinfo->columns[col];
		collen = _get_printable_size(colinfo);
		namlen = colinfo->column_namelen;
		padlen = (collen > namlen ? collen : namlen) - namlen;
		if (buf_len < namlen) {
			return FAIL;
		}
		strncpy(buffer, colinfo->column_name, namlen);
		buffer += namlen;
		if ((c = dbstring_getchar(dbproc->dbopts[DBPRPAD].param, 0)) == -1) {
			c = ' ';
		}
		for (; padlen > 0; padlen--) {
			if (buf_len < 1) {
				return FAIL;
			}
			*buffer++ = c;
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
