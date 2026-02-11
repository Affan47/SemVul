tds_bcp_row_free(TDSRESULTINFO* result, unsigned char *row)
{
	result->row_size = 0;
	TDS_ZERO_FREE(result->current_row);
}
