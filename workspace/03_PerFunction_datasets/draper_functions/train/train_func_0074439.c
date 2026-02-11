G_get_raster_sample_nearest(
    int fd,
    const struct Cell_head *window,
    struct Categories *cats,
    double north, double east, int usedesc)
{
    int row, col;
    DCELL result;
    DCELL *maprow = G_allocate_d_raster_buf();


    row = (int)floor(G_northing_to_row(north, window));
    col = (int)floor(G_easting_to_col(east, window));

    if (row < 0 || row >= G_window_rows() ||
	col < 0 || col >= G_window_cols()) {
	G_set_d_null_value(&result, 1);
	goto done;
    }

    if (G_get_d_raster_row(fd, maprow, row) < 0)
	raster_row_error(window, north, east);

    if (G_is_d_null_value(&maprow[col])) {
	G_set_d_null_value(&result, 1);
	goto done;
    }

    if (usedesc) {
	char *buf = G_get_cat(maprow[col], cats);

	G_squeeze(buf);
	result = scancatlabel(buf);
    }
    else
	result = maprow[col];

done:
    G_free(maprow);

    return result;
}
