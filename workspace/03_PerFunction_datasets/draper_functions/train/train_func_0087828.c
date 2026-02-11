dump_results_pp(FILE *out, MdbSQL *sql)
{
	unsigned int j;
	MdbSQLColumn *sqlcol;
	unsigned long row_count = 0;


	if (headers) {
		for (j=0;j<sql->num_columns;j++) {
			sqlcol = g_ptr_array_index(sql->columns,j);
			if (strlen(sqlcol->name)>sqlcol->disp_size)
				sqlcol->disp_size = strlen(sqlcol->name);
			print_break(out, sqlcol->disp_size, !j);
		}
		fprintf(out,"\n");
		fflush(out);
		for (j=0;j<sql->num_columns;j++) {
			sqlcol = g_ptr_array_index(sql->columns,j);
			print_value(out, sqlcol->name,sqlcol->disp_size,!j);
		}
		fprintf(out,"\n");
		fflush(out);
	}

	for (j=0;j<sql->num_columns;j++) {
		sqlcol = g_ptr_array_index(sql->columns,j);
		print_break(out, sqlcol->disp_size, !j);
	}
	fprintf(out,"\n");
	fflush(out);


	while(mdb_fetch_row(sql->cur_table)) {
		row_count++;
  		for (j=0;j<sql->num_columns;j++) {
			sqlcol = g_ptr_array_index(sql->columns,j);
			print_value(out, sql->bound_values[j],sqlcol->disp_size,!j);
		}
		fprintf(out,"\n");
		fflush(out);
	}


	for (j=0;j<sql->num_columns;j++) {
		sqlcol = g_ptr_array_index(sql->columns,j);
		print_break(out, sqlcol->disp_size, !j);
	}
	fprintf(out,"\n");
	fflush(out);
	if (footers) {
		print_rows_retrieved(out, row_count);
	}


	for (j=0;j<sql->num_columns;j++) {
		g_free(sql->bound_values[j]);
	}

	mdb_sql_reset(sql);
}
