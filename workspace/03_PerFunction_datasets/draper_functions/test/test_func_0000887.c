configure_plot(void)
{
    int i, j;
    int nrows;
    int ncols;

    nrows = region.rows - at_row;
    if (nrows <= 0)
	return 1;

    if (nrows > max_rows)
	nrows = max_rows;

    ncols = region.cols;


    switch (format) {
    case USE_CELL:
	for (i = 0; i < nrows; i++)
	    for (j = 0; j < ncols; j++)
		raster.cell[i][j] = 0;
	break;
    case USE_DCELL:
	for (i = 0; i < nrows; i++)
	    for (j = 0; j < ncols; j++)
		raster.dcell[i][j] = 0;
	break;
    }

    for (i = 0; i < nrows; i++)
	for (j = 0; j < ncols; j++)
	    null_flags[i][j] = 1;


    page.north = region.north - at_row * region.ns_res;
    page.south = page.north - nrows * region.ns_res;
    G_set_window(&page);


    G_setup_plot(-0.5, page.rows - 0.5, -0.5, page.cols - 0.5, move, cont);

    return 0;
}
