df_set_read_type(int col, df_data_type type)
{
    assert(col > 0);

    if (col > df_max_bininfo_cols) {
	df_column_bininfo = gp_realloc(df_column_bininfo,
				       col * sizeof(df_column_bininfo_struct),
				       "datafile columns binary information");
	df_max_bininfo_cols = col;
    }
    df_column_bininfo[col-1].column.read_type = type;
    df_column_bininfo[col-1].column.read_size
	= df_binary_details[type].type.read_size;
}
