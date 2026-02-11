gnumeric_get_link (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	GnmValue const * const v = argv[0];

	if (v->type == VALUE_CELLRANGE) {
		GnmCellRef const * a = &v->v_range.cell.a;
		GnmCellRef const * b = &v->v_range.cell.b;
		Sheet *sheet;
		GnmHLink *link;
		GnmCellPos pos;

		if (a->col != b->col || a->row != b->row || a->sheet !=b->sheet)
			return value_new_error_REF (ei->pos);

		sheet = (a->sheet == NULL) ? ei->pos->sheet : a->sheet;
		gnm_cellpos_init_cellref (&pos, a, &(ei->pos->eval), sheet);
		link = sheet_hlink_find (sheet, &pos);

		if (link)
			return value_new_string (gnm_hlink_get_target (link));
	}

	return value_new_empty ();
}
