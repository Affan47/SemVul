describePuzzle (int xDim, int yDim, int zDim, int shMoves)
{
    QString descr;
    if ((xDim == yDim) && (yDim == zDim)) {
	descr = i18n ("%1x%2x%3 cube, %4 shuffling moves",
			xDim, yDim, zDim, shMoves);
    }
    else if ((xDim != 1) && (yDim != 1) && (zDim != 1)) {
	descr = i18n ("%1x%2x%3 brick, %4 shuffling moves",
			xDim, yDim, zDim, shMoves);
    }
    else {
	descr = i18n ("%1x%2x%3 mat, %4 shuffling moves",
			xDim, yDim, zDim, shMoves);
    }
    statusBar()->changeItem (descr, 1001);
}
