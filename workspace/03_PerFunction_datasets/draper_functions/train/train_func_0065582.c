in_range(LayerTable *tbl, int key)
{
	int lo, hi;

	lo = LOWNUM(tbl->val[SF_keyRange]);
	hi = HIGHNUM(tbl->val[SF_keyRange]);
	if (key >= lo && key <= hi)
		return TRUE;
	return FALSE;
}
