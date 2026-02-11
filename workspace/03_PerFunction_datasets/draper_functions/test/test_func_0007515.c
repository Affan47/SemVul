tds_row_free(TDSRESULTINFO *res_info, unsigned char *row)
{
	int i;
	const TDSCOLUMN *col;

	if (!res_info || !row)
		return;

	for (i = 0; i < res_info->num_cols; ++i) {
		col = res_info->columns[i];

		if (is_blob_col(col)) {
			TDSBLOB *blob = (TDSBLOB *) &row[col->column_data - res_info->current_row];
			if (blob->textvalue)
				TDS_ZERO_FREE(blob->textvalue);
		}
	}

	free(row);
}
