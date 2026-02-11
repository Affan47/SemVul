table_sorter_sort (ETableSorter *table_sorter)
{
	gint rows;
	gint i;
	gint j;
	gint cols;
	gint group_cols;
	struct qsort_data qd;

	if (table_sorter->sorted)
		return;

	rows = e_table_model_row_count (table_sorter->source);
	group_cols = e_table_sort_info_grouping_get_count (table_sorter->sort_info);
	cols = e_table_sort_info_sorting_get_count (table_sorter->sort_info) + group_cols;

	table_sorter->sorted = g_new (int, rows);
	for (i = 0; i < rows; i++)
		table_sorter->sorted[i] = i;

	qd.cols = cols;
	qd.table_sorter = table_sorter;

	qd.vals = g_new (gpointer , rows * cols);
	qd.ascending = g_new (int, cols);
	qd.compare = g_new (GCompareDataFunc, cols);
	qd.cmp_cache = e_table_sorting_utils_create_cmp_cache ();

	for (j = 0; j < cols; j++) {
		ETableColumnSpecification *spec;
		ETableCol *col;
		GtkSortType sort_type;

		if (j < group_cols)
			spec = e_table_sort_info_grouping_get_nth (
				table_sorter->sort_info,
				j, &sort_type);
		else
			spec = e_table_sort_info_sorting_get_nth (
				table_sorter->sort_info,
				j - group_cols, &sort_type);

		col = e_table_header_get_column_by_spec (
			table_sorter->full_header, spec);
		if (col == NULL) {
			gint last = e_table_header_count (
				table_sorter->full_header) - 1;
			col = e_table_header_get_column (
				table_sorter->full_header, last);
		}

		for (i = 0; i < rows; i++) {
			qd.vals[i * cols + j] = e_table_model_value_at (
				table_sorter->source,
				col->spec->model_col, i);
		}

		qd.compare[j] = col->compare;
		qd.ascending[j] = (sort_type == GTK_SORT_ASCENDING);
	}

	g_qsort_with_data (table_sorter->sorted, rows, sizeof (gint), qsort_callback, &qd);

	g_free (qd.vals);
	g_free (qd.ascending);
	g_free (qd.compare);
	e_table_sorting_utils_free_cmp_cache (qd.cmp_cache);
}
