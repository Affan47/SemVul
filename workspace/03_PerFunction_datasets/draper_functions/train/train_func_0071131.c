get_map(int col, int row, schar bg_typ)
{
	if (col <= 0 || row < 0 || col > WIDTH || row >= HEIGHT)
		return bg_typ;
	return levl[col][row].typ;
}
