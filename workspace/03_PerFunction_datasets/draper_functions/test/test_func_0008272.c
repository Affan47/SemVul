getCursorPosition(int &row, int &col)
{
	if (currentRow < 0)
	{
		row=0;
		col=0;
		CursesVScroll::getCursorPosition(row, col);
		return 0;
	}

	size_t h=directory.size()/2;

	size_t w=getWidth()/2;

	if (w > 2)
		--w;

	if (w <= 0)
		w=1;

	row=currentRow;
	col=w-1;

	if ( (size_t)currentRow >= h)
	{
		row -= h;
		col += w+2;
	}
	CursesVScroll::getCursorPosition(row, col);
	return 0;
}
