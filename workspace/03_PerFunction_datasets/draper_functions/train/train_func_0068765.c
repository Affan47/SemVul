tds9_get_varmax(TDSSOCKET * tds, TDSCOLUMN * curcol)
{
	TDS_INT8 len = tds_get_int8(tds);
	TDS_INT chunk_len;
	TDS_CHAR **p;
	size_t offset;


	if (len == -1) {
		curcol->column_cur_size = -1;
		return TDS_SUCCEED;
	}

	curcol->column_cur_size = 0;
	offset = 0;
	p = &(((TDSBLOB*) curcol->column_data)->textvalue);
	for (;;) {
		TDS_CHAR *tmp;

		chunk_len = tds_get_int(tds);
		if (chunk_len <= 0) {
			curcol->column_cur_size = offset;
			return TDS_SUCCEED;
		}
		if (*p == NULL)
			tmp = (TDS_CHAR*) malloc(chunk_len);
		else
			tmp = (TDS_CHAR*) realloc(*p, offset + chunk_len);
		if (!tmp)
			return TDS_FAIL;
		*p = tmp;
		tds_get_n(tds, *p + offset, chunk_len);
		offset += chunk_len;
	}
	return TDS_SUCCEED;
}
