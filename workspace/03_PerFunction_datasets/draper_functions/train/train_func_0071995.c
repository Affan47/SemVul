sheet_col_is_hidden (Sheet const *sheet, int col)
{
	ColRowInfo const * const res = sheet_col_get (sheet, col);
	return (res != NULL && !res->visible);
}
