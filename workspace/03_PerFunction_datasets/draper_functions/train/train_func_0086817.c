calcwidth(VOID_A)
{
	int col, w1, width;

	col = n_column;
	if (ispureshift()) col++;
	width = (col / FILEPERLINE) - 2 - 1 + ((isshortwid()) ? 1 : 0);
	w1 = WIDTH1;
	if (curcolumns < 2 && width - (w1 + WIDTH2 + WIDTH3) >= minfilename)
		width -= w1 + WIDTH2 + WIDTH3;
	else if (curcolumns < 3 && width - (WIDTH2 + WIDTH3) >= minfilename)
		width -= WIDTH2 + WIDTH3;
	else if (curcolumns < 4 && width - WIDTH3 >= minfilename)
		width -= WIDTH3;

	return(width);
}
