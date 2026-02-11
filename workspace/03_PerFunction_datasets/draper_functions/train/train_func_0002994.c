gnm_sheet_range_from_value (GnmSheetRange *r, GnmValue const *v)
{
	g_return_val_if_fail (v->type == VALUE_CELLRANGE, FALSE);

	r->sheet = v->v_range.cell.a.sheet;
	range_init_value (&r->range, v);

	return TRUE;
}
