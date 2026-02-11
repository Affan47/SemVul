odbc_set_return_status(struct _hstmt *stmt, unsigned int n_row)
{
	TDSSOCKET *tds = stmt->dbc->tds_socket;


	if (stmt->prepared_query_is_func && tds->has_status) {
		struct _drecord *drec;
		int len;
		const TDS_DESC* axd = stmt->apd;
		TDS_INTPTR len_offset;
		char *data_ptr;

		if (axd->header.sql_desc_count < 1)
			return;
		drec = &axd->records[0];
		data_ptr = drec->sql_desc_data_ptr;

		if (axd->header.sql_desc_bind_type != SQL_BIND_BY_COLUMN) {
			len_offset = axd->header.sql_desc_bind_type * n_row;
			if (axd->header.sql_desc_bind_offset_ptr)
				len_offset += *axd->header.sql_desc_bind_offset_ptr;
			data_ptr += len_offset;
		} else {
			len_offset = sizeof(SQLLEN) * n_row;
			data_ptr += sizeof(SQLINTEGER) * n_row;
		}
#define LEN(ptr) *((SQLLEN*)(((char*)(ptr)) + len_offset))

		len = odbc_tds2sql(stmt, NULL, SYBINT4, (TDS_CHAR *) & tds->ret_status, sizeof(TDS_INT),
				   drec->sql_desc_concise_type, (void *) data_ptr, drec->sql_desc_octet_length, NULL);
		if (len == SQL_NULL_DATA)
			return  ;
		if (drec->sql_desc_indicator_ptr)
			LEN(drec->sql_desc_indicator_ptr) = 0;
		if (drec->sql_desc_octet_length_ptr)
			LEN(drec->sql_desc_octet_length_ptr) = len;
	}
#undef LEN
}
