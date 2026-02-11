colrow_visibility (Sheet const *sheet, ColRowVisiblity * const dat,
		   int first, int last)
{
	int i;
	gboolean const visible = dat->visible;
	ColRowInfo * (*get) (Sheet const *sheet, int pos) = (dat->is_cols)
		? &sheet_col_get : &sheet_row_get;


	for (i = last; i >= first; --i) {
		int j;
		ColRowIndex *res;
		ColRowInfo const *cri = (*get) (sheet, i);

		if (cri == NULL) {
			if (visible != 0)
				continue;
		} else if ((visible != 0) == (cri->visible != 0))
			continue;


		for (j = i; j >= first ; --j) {
			cri = (*get) (sheet, j);
			if (cri == NULL) {
				if (visible != 0)
					break;
			} else if ((visible != 0) == (cri->visible != 0))
				break;
			else if (cri->is_collapsed) {
				--j;
				break;
			}
		}
		res = g_new (ColRowIndex, 1);
		res->first = (j >= first) ? j+1 : first;
		res->last = i;
#if 0
		g_printerr ("%d %d\n", res->index, res->count);
#endif
		dat->elements = g_slist_insert_sorted (dat->elements, res,
					(GCompareFunc)colrow_index_cmp);

		if (visible && cri != NULL && cri->is_collapsed) {
			i = colrow_find_outline_bound (
				sheet, dat->is_cols, j,
				cri->outline_level+1, FALSE);
		} else
			i = j;
	}
}
