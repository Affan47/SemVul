load_window_values(FCELL ** in_rows, FCELL window[][3],
			int rows, int cols, int row, int col)
{
    int i, j;

    rows -= 1;
    cols -= 1;

    for (i = -1; i < 2; i++) {
	if (row + i < 0 || row + i > rows) {
	    window[i + 1][0] = 0;
	    window[i + 1][1] = 0;
	    window[i + 1][2] = 0;
	    continue;
	}
	else {
	    for (j = -1; j < 2; j++) {
		if (col + j < 0 || col + j > cols - 1) {
		    window[i + 1][j + 1] = 0;
		    continue;
		}
		else {
		    window[i + 1][j + 1] = in_rows[row + i][col + j];
		}
	    }
	}
    }
}
