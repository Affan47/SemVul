StoreEndOfLine(int row, int col)
{
	LINE *	line;


	if ((row < 0) || (row >= rows) || (col < 0) || (col >= cols))
		return;


	while (col < cols)
		StoreCharacter(row, col++, ' ');


	line = GetLine(row);
#if 0


	if (col < line->usedCount)
	{
		line->clearCount = line->usedCount - col;
		line->usedCount = col;
	}
#endif
}
