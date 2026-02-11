CanShowColumn(const COLUMN * column, int col)
{
	if (column == NULL)
		return FALSE;

	if (column->justify == LEFT)
		return (col + column->minWidth <= outputWidth);

	return (col + column->width <= outputWidth);
}
