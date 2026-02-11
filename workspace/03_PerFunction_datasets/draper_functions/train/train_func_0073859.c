sorter_array_backsort (ESorterArray *sorter_array)
{
	gint i, rows;

	if (sorter_array->backsorted)
		return;

	sorter_array_sort (sorter_array);

	rows = sorter_array->rows;

	sorter_array->backsorted = g_new0 (gint, rows);

	for (i = 0; i < rows; i++)
		sorter_array->backsorted[sorter_array->sorted[i]] = i;
}
