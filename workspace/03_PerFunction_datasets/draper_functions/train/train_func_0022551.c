ms_excel_chart_read_LABEL (BiffQuery *q, XLChartReadState *state)
{
	guint16 row, sernum;
	char *label;
	XLChartSeries *series;

	XL_CHECK_CONDITION (q->length >= 6);
	row = GSF_LE_GET_GUINT16 (q->data + 0);
	sernum = GSF_LE_GET_GUINT16 (q->data + 2);


	if (state->series == NULL || state->cur_role < 0)
		return;
	XL_CHECK_CONDITION (state->cur_role < GOG_MS_DIM_TYPES);
	XL_CHECK_CONDITION (sernum < state->series->len);

	series = g_ptr_array_index (state->series, sernum);
	if (series == NULL)
		return;

	label = excel_biff_text_2 (state->container.importer, q, 6);
	if (label != NULL  &&
	    series->data[state->cur_role].value != NULL) {
		XL_CHECK_CONDITION (row < (guint)series->data[state->cur_role].num_elements);

		value_release (series->data[state->cur_role].value->vals[0][row]);
		series->data[state->cur_role].value->vals[0][row] = value_new_string (label);
	}
	d (10, {g_printerr ("'%s' row = %d, series = %d\n", label, row, sernum);});
	g_free (label);
}
