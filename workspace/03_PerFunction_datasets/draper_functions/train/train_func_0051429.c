do_column_filling_wday (data_analysis_output_t *dao, fill_series_t *info)
{
	int i;
	gnm_float start = info->start_value;
	GDate        date;
	GODateConventions const *conv =
		workbook_date_conv (dao->sheet->workbook);


	for (i = 0; i < info->n; i++) {
		int steps = (i * info->step_value) + 0.5;
		int days = (steps / 5) * 7 + steps % 5;
		GDateWeekday wd;

		go_date_serial_to_g (&date, start, conv);
		wd = g_date_get_weekday (&date);
		if (wd + (steps % 5) > G_DATE_FRIDAY)
				days += 2;
		gnm_date_add_days (&date, days);

		dao_set_cell_float (dao, 0,i,
				    go_date_g_to_serial (&date, conv));
	}


}
