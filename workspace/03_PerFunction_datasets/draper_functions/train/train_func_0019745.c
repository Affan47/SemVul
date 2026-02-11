row_dotted_fill(int y, double x1, double x2)
{
    int i1, i2, i;

    if (y != iceil(y / dotted_fill_gap) * dotted_fill_gap)
	return 0;

    i1 = iceil(x1 / dotted_fill_gap) * dotted_fill_gap;
    i2 = ifloor(x2);
    if (i1 <= i2) {
	for (i = i1; i <= i2; i += dotted_fill_gap) {
	    move(i, y);
	    cont(i, y);
	}
    }

    return 0;
}
