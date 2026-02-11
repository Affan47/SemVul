ddSiftUp(
  DdManager * table,
  int  x,
  int  xLow)
{
    int        y;
    int        size;

    y = cuddNextLow(table,x);
    while (y >= xLow) {
	size = cuddSwapInPlace(table,y,x);
	if (size == 0) {
	    return(0);
	}
	x = y;
	y = cuddNextLow(table,x);
    }
    return(1);

}
