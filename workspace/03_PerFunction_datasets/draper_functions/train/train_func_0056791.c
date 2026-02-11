drv_generic_graphic_resizeFB(int rows, int cols)
{
    RGBA *newFB;
    int i, l, row, col;


    if (rows <= LROWS && cols <= LCOLS)
	return;


    if (rows < LROWS)
	rows = LROWS;
    if (cols < LCOLS)
	cols = LCOLS;

    for (l = 0; l < LAYERS; l++) {


	newFB = malloc(cols * rows * sizeof(*newFB));
	for (i = 0; i < rows * cols; i++)
	    newFB[i] = NO_COL;


	if (drv_generic_graphic_FB[l] != NULL) {
	    for (row = 0; row < LROWS; row++) {
		for (col = 0; col < LCOLS; col++) {
		    newFB[row * cols + col] = drv_generic_graphic_FB[l][row * LCOLS + col];
		}
	    }
	    free(drv_generic_graphic_FB[l]);
	}
	drv_generic_graphic_FB[l] = newFB;
    }

    LCOLS = cols;
    LROWS = rows;

}
