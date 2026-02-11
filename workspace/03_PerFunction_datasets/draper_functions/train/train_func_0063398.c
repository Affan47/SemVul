withinBounds(loopstruct * lp, int col, int row)
{
	return (row >= 1 && row < lp->bnrows - 1 &&
		col >= 1 && col < lp->bncols - 1 - (local_neighbors == 6 && (row % 2)));
}
