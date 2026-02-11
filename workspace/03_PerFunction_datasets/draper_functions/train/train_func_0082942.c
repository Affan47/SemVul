link_unlink_cellrange_dep (GnmDependent *dep, GnmCellPos const *pos,
			   GnmCellRef const *a, GnmCellRef const *b,
			   gboolean qlink)
{
	DependencyRange range;
	GnmDependentFlags flag = DEPENDENT_NO_FLAG;

	gnm_cellpos_init_cellref (&range.range.start, a, pos, dep->sheet);
	gnm_cellpos_init_cellref (&range.range.end, b, pos, dep->sheet);
	range_normalize (&range.range);

	if (a->sheet != NULL) {
		if (a->sheet != dep->sheet)
			flag = (a->sheet->workbook != dep->sheet->workbook)
				? DEPENDENT_GOES_INTERBOOK : DEPENDENT_GOES_INTERSHEET;

		if (b->sheet != NULL && a->sheet != b->sheet) {
			Workbook const *wb = a->sheet->workbook;
			int i = a->sheet->index_in_wb;
			int stop = b->sheet->index_in_wb;
			if (i > stop) { int tmp = i; i = stop ; stop = tmp; }

			g_return_val_if_fail (b->sheet->workbook == wb, flag);

			while (i <= stop) {
				Sheet *sheet = g_ptr_array_index (wb->sheets, i);
				i++;
				link_unlink_range_dep (sheet->deps, dep, &range,
						       qlink);
			}
			flag |= DEPENDENT_HAS_3D;
		} else
			link_unlink_range_dep (a->sheet->deps, dep, &range,
					       qlink);
	} else
		link_unlink_range_dep (dep->sheet->deps, dep, &range, qlink);

	return flag;
}
