odbc_col_setname(TDS_STMT * stmt, int colpos, const char *name)
{
#if ENABLE_EXTRA_CHECKS
	TDSRESULTINFO *resinfo;
#endif

	IRD_CHECK;

#if ENABLE_EXTRA_CHECKS
	if (colpos > 0 && stmt->dbc->tds_socket != NULL && (resinfo = stmt->dbc->tds_socket->current_results) != NULL) {
		if (colpos <= resinfo->num_cols) {

			strcpy(resinfo->columns[colpos - 1]->column_name, name);
			resinfo->columns[colpos - 1]->column_namelen = strlen(name);
			if (resinfo->columns[colpos - 1]->table_column_name)
				TDS_ZERO_FREE(resinfo->columns[colpos - 1]->table_column_name);
		}
	}
#endif

	if (colpos > 0 && colpos <= stmt->ird->header.sql_desc_count) {
		--colpos;
		tds_dstr_copy(&stmt->ird->records[colpos].sql_desc_label, name);
		tds_dstr_copy(&stmt->ird->records[colpos].sql_desc_name, name);
	}
}
