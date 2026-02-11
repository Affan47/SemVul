get_multiplot_layout (int n, int tseries,
				  int *rows, int *cols)
{
    if (n < 3) {
	if (tseries) {
	    *cols = 1;
	    *rows = 2;
	} else {
	    *cols = 2;
	    *rows = 1;
	}
    } else if (n < 5) {
	*cols = *rows = 2;
    } else if (n < 7) {
	*cols = 3;
	*rows = 2;
    } else if (n < 10) {
	*cols = *rows = 3;
    } else if (n < 13) {
	*cols = 4;
	*rows = 3;
    } else if (n < 17) {
	*cols = *rows = 4;
    } else {
	*cols = *rows = 0;
    }
}
