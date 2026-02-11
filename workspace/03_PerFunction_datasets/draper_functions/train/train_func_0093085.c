calcTileRect(int pos, int numRows, int numCols, int leftOver, const Bounds &b, Bounds &nB)
{
	int x, y;

	int d = (numCols - leftOver) * numRows;
	if (pos <  d) {
		x = pos / numRows;
		y = pos % numRows;
	} else {
		x = (pos-d)/(numRows+1) + (numCols-leftOver);
		y = (pos-d)%(numRows+1);
	}
	nB.x = dividerLoc(b.x, b.x+b.w, numCols, x);
	nB.w = dividerLoc(b.x, b.x+b.w, numCols, x+1) - nB.x;
	if (pos >= d) {
		nB.y = dividerLoc(b.y, b.y+b.h, numRows+1, y);
		nB.h = dividerLoc(b.y, b.y+b.h, numRows+1, y+1) - nB.y;
	} else {
		nB.y = dividerLoc(b.y, b.y+b.h, numRows, y);
		nB.h = dividerLoc(b.y, b.y+b.h, numRows, y+1) - nB.y;
	}
}
