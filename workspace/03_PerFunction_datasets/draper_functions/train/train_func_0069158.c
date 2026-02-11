tds_process_params_result_token(TDSSOCKET * tds)
{
	int i;
	TDSCOLUMN *curcol;
	TDSPARAMINFO *info;

	CHECK_TDS_EXTRA(tds);


	info = tds->current_results;
	if (!info)
		return TDS_FAIL;

	for (i = 0; i < info->num_cols; i++) {
		curcol = info->columns[i];
		if (tds_get_data(tds, curcol) != TDS_SUCCEED)
			return TDS_FAIL;
	}
	return TDS_SUCCEED;
}
