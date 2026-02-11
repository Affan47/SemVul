tds_put_data_info(TDSSOCKET * tds, TDSCOLUMN * curcol, int flags)
{
	int len;

	CHECK_TDS_EXTRA(tds);
	CHECK_COLUMN_EXTRA(curcol);

	if (flags & TDS_PUT_DATA_USE_NAME) {
		len = curcol->column_namelen;
		tdsdump_log(TDS_DBG_ERROR, "tds_put_data_info putting param_name \n");

		if (IS_TDS7_PLUS(tds)) {
			size_t converted_param_len;
			const char *converted_param;


			converted_param =
				tds_convert_string(tds, tds->char_convs[client2ucs2], curcol->column_name, len,
						   &converted_param_len);
			if (!converted_param)
				return TDS_FAIL;
			if (!(flags & TDS_PUT_DATA_PREFIX_NAME)) {
				TDS_PUT_BYTE(tds, converted_param_len / 2);
			} else {
				TDS_PUT_BYTE(tds, converted_param_len / 2 + 1);
				tds_put_n(tds, "@", 2);
			}
			tds_put_n(tds, converted_param, converted_param_len);
			tds_convert_string_free(curcol->column_name, converted_param);
		} else {

			tds_put_byte(tds, len);
			tds_put_n(tds, curcol->column_name, len);
		}
	} else {
		tds_put_byte(tds, 0x00);
	}


	tdsdump_log(TDS_DBG_ERROR, "tds_put_data_info putting status \n");
	tds_put_byte(tds, curcol->column_output);
	if (!IS_TDS7_PLUS(tds))
		tds_put_int(tds, curcol->column_usertype);

	tds_put_byte(tds, curcol->on_server.column_type);

	if (is_numeric_type(curcol->on_server.column_type)) {
#if 1
		tds_put_byte(tds, tds_numeric_bytes_per_prec[curcol->column_prec]);
		tds_put_byte(tds, curcol->column_prec);
		tds_put_byte(tds, curcol->column_scale);
#else
		TDS_NUMERIC *num = (TDS_NUMERIC *) curcol->column_data;
		tds_put_byte(tds, tds_numeric_bytes_per_prec[num->precision]);
		tds_put_byte(tds, num->precision);
		tds_put_byte(tds, num->scale);
#endif
	} else {
		size_t size = tds_fix_column_size(tds, curcol);
		switch (curcol->column_varint_size) {
		case 0:
			break;
		case 1:
			tds_put_byte(tds, size);
			break;
		case 2:
			tds_put_smallint(tds, size);
			break;
		case 5:
		case 4:
			tds_put_int(tds, size);
			break;
		case 8:
			tds_put_smallint(tds, 0xffff);
			break;
		}
	}


	if (IS_TDS71_PLUS(tds) && is_collate_type(curcol->on_server.column_type))
		tds_put_n(tds, tds->collation, 5);


	if (!IS_TDS7_PLUS(tds)) {

		tdsdump_log(TDS_DBG_ERROR, "HERE! \n");
		tds_put_byte(tds, 0x00);
	}
	return TDS_SUCCEED;
}
