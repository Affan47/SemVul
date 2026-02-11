get_map_row_nomask(int fd, void *rast, int row,
			      RASTER_MAP_TYPE data_type)
{
    static void (*transfer_to_cell_FtypeOtype[3][3]) () = { {
    transfer_to_cell_XX, transfer_to_cell_if, transfer_to_cell_id}, {
    transfer_to_cell_fi, transfer_to_cell_XX, transfer_to_cell_fd}, {
    transfer_to_cell_di, transfer_to_cell_df, transfer_to_cell_XX}};
    struct fileinfo *fcb = &G__.fileinfo[fd];
    int r;
    int rowStatus;

    rowStatus = compute_window_row(fd, row, &r);

    if (rowStatus <= 0) {
	fcb->cur_row = -1;
	G_zero_raster_buf(rast, data_type);
	return rowStatus;
    }


    if (r != fcb->cur_row) {
	fcb->cur_row = r;

	if (read_data(fd, fcb->cur_row, fcb->data, &fcb->cur_nbytes) < 0) {
	    G_zero_raster_buf(rast, data_type);

	    if (!fcb->io_error) {
		if (fcb->cellhd.compressed)
		    G_warning(_("Error reading compressed map <%s@%s>, row %d"),
			      fcb->name, fcb->mapset, r);
		else
		    G_warning(_("Error reading map <%s@%s>, row %d"),
			      fcb->name, fcb->mapset, r);

		fcb->io_error = 1;
	    }
	    return -1;
	}
    }

    (transfer_to_cell_FtypeOtype[fcb->map_type][data_type]) (fd, rast);

    return 1;
}
