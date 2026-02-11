blk_bind(CS_BLKDESC * blkdesc, CS_INT item, CS_DATAFMT * datafmt, CS_VOID * buffer, CS_INT * datalen, CS_SMALLINT * indicator)
{
	TDSCOLUMN *colinfo;
	CS_CONNECTION *con;
	CS_INT bind_count;
	int i;

	tdsdump_log(TDS_DBG_FUNC, "blk_bind(%p, %d, %p, %p, %p, %p)\n", blkdesc, item, datafmt, buffer, datalen, indicator);

	if (!blkdesc) {
		return CS_FAIL;
	}
	con = blkdesc->con;

	if (item == CS_UNUSED) {

		if (datafmt == NULL && buffer == NULL && datalen == NULL && indicator == NULL ) {
			blkdesc->bcpinfo.bind_count = CS_UNUSED;
			for (i = 0; i < blkdesc->bcpinfo.bindinfo->num_cols; i++ ) {
				colinfo = blkdesc->bcpinfo.bindinfo->columns[i];
				colinfo->column_varaddr  = NULL;
				colinfo->column_bindtype = 0;
				colinfo->column_bindfmt  = 0;
				colinfo->column_bindlen  = 0;
				colinfo->column_nullbind = NULL;
				colinfo->column_lenbind  = NULL;
			}
		}
		return CS_SUCCEED;
	}


	if (item < 1 || item > blkdesc->bcpinfo.bindinfo->num_cols) {
		_ctclient_msg(con, "blk_bind", 2, 5, 1, 141, "%s, %d", "colnum", item);
		return CS_FAIL;
	}


	if (datafmt == NULL && buffer == NULL && datalen == NULL && indicator == NULL ) {

		colinfo = blkdesc->bcpinfo.bindinfo->columns[item - 1];
		colinfo->column_varaddr  = NULL;
		colinfo->column_bindtype = 0;
		colinfo->column_bindfmt  = 0;
		colinfo->column_bindlen  = 0;
		colinfo->column_nullbind = NULL;
		colinfo->column_lenbind  = NULL;

		return CS_SUCCEED;
	}


	bind_count = (datafmt->count == 0) ? 1 : datafmt->count;


	if (blkdesc->bcpinfo.bind_count == CS_UNUSED) {
		blkdesc->bcpinfo.bind_count = bind_count;
	} else {

		if (blkdesc->bcpinfo.bind_count != bind_count) {
			_ctclient_msg(con, "blk_bind", 1, 1, 1, 137, "%d, %d", bind_count, blkdesc->bcpinfo.bind_count);
			return CS_FAIL;
		}
	}


	colinfo = blkdesc->bcpinfo.bindinfo->columns[item - 1];

	colinfo->column_varaddr = (char *) buffer;
	colinfo->column_bindtype = datafmt->datatype;
	colinfo->column_bindfmt = datafmt->format;
	colinfo->column_bindlen = datafmt->maxlength;
	if (indicator) {
		colinfo->column_nullbind = indicator;
	}
	if (datalen) {
		colinfo->column_lenbind = datalen;
	}
	return CS_SUCCEED;
}
