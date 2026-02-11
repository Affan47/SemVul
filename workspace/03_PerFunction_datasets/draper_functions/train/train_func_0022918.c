sheet_destroy_contents (Sheet *sheet)
{

	int const max_col = sheet->cols.max_used;
	int const max_row = sheet->rows.max_used;
	GSList *filters;
	int i;


	g_return_if_fail (sheet->deps == NULL);


	if (sheet->hash_merged == NULL)
		return;

	{
		GSList *tmp = sheet->slicers;
		sheet->slicers = NULL;
		g_slist_free_full (tmp, (GDestroyNotify)gnm_sheet_slicer_clear_sheet);
	}


	filters = g_slist_copy (sheet->filters);
	g_slist_foreach (filters, (GFunc)gnm_filter_remove, NULL);
	g_slist_foreach (filters, (GFunc)gnm_filter_unref, NULL);
	g_slist_free (filters);

	if (sheet->sheet_objects) {

		GSList *objs = g_slist_copy (sheet->sheet_objects);
		GSList *ptr;
		for (ptr = objs; ptr != NULL ; ptr = ptr->next) {
			SheetObject *so = SHEET_OBJECT (ptr->data);
			if (so != NULL)
				sheet_object_clear_sheet (so);
		}
		g_slist_free (objs);
		if (sheet->sheet_objects != NULL)
			g_warning ("There is a problem with sheet objects");
	}


	g_hash_table_destroy (sheet->hash_merged);
	sheet->hash_merged = NULL;

	g_slist_free_full (sheet->list_merged, g_free);
	sheet->list_merged = NULL;


	for (i = sheet->rows.max_used; i >= 0 ; --i)
		row_destroy_span (sheet_row_get (sheet, i));


	sheet_cell_foreach (sheet, (GHFunc) &cb_remove_allcells, NULL);
	g_hash_table_destroy (sheet->cell_hash);


	for (i = 0; i <= max_col; ++i)
		sheet_col_destroy (sheet, i, FALSE);

	for (i = 0; i <= max_row; ++i)
		sheet_row_destroy (sheet, i, FALSE);


	colrow_resize (&sheet->cols, 0);
	g_ptr_array_free (sheet->cols.info, TRUE);
	sheet->cols.info = NULL;

	colrow_resize (&sheet->rows, 0);
	g_ptr_array_free (sheet->rows.info, TRUE);
	sheet->rows.info = NULL;

	g_clear_object (&sheet->solver_parameters);
}
