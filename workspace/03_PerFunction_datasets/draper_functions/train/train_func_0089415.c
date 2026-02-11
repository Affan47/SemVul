corr(int x, int y)
{
	if (rn2(50)) {
		levl[x][y].typ = CORR;
	} else {
		levl[x][y].typ = SCORR;
	}
}
