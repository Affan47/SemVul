paramrowalloc(TDSPARAMINFO * params, TDSCOLUMN * curcol, int param_num, void *value, int size)
{
	const void *row = tds_alloc_param_data(curcol);

	tdsdump_log(TDS_DBG_INFO1, "paramrowalloc, size = %d, data = %p, row_size = %d\n",
				size, curcol->column_data, params->row_size);
	if (!row)
		return NULL;

	if (value) {

		if (size > curcol->column_size) {
			tdsdump_log(TDS_DBG_FUNC, "paramrowalloc(): RESIZE %d to %d\n", size, curcol->column_size);
			size = curcol->column_size;
		}

		if (!is_blob_col(curcol))
			memcpy(curcol->column_data, value, size);
		else {
			TDSBLOB *blob = (TDSBLOB *) curcol->column_data;
			blob->textvalue = malloc(size);
			tdsdump_log(TDS_DBG_FUNC, "blob parameter supported, size %d textvalue pointer is %p\n",
					size, blob->textvalue);
			if (!blob->textvalue)
				return NULL;
			memcpy(blob->textvalue, value, size);
		}
		curcol->column_cur_size = size;
	} else {
		tdsdump_log(TDS_DBG_FUNC, "paramrowalloc(): setting parameter #%d to NULL\n", param_num);
		curcol->column_cur_size = -1;
	}

	return row;
}
