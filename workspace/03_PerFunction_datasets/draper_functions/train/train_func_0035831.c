cb_assign_string (GnmCellIter const *iter, GPtrArray *strs)
{
	GnmValue *v = NULL;

	if (iter->cell != NULL) {
		gnm_cell_eval (iter->cell);
		v = iter->cell->value;
	}
	g_ptr_array_add (strs, v);

	return NULL;
}
