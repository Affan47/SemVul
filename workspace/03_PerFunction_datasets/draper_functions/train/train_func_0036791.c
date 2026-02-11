sorter_array_sort (ESorterArray *sorter_array)
{
	gint rows;
	gint i;

	if (sorter_array->sorted)
		return;

	rows = sorter_array->rows;

	sorter_array->sorted = g_new (gint, rows);
	for (i = 0; i < rows; i++)
		sorter_array->sorted[i] = i;

	if (sorter_array->compare) {
		if (sorter_array->create_cmp_cache)
			sorter_array->cmp_cache =
				sorter_array->create_cmp_cache (
				sorter_array->closure);

		g_qsort_with_data (
			sorter_array->sorted, rows, sizeof (gint),
			esort_callback, sorter_array);

		if (sorter_array->cmp_cache) {
			g_hash_table_destroy (sorter_array->cmp_cache);
			sorter_array->cmp_cache = NULL;
		}
	}
}
