cell_stats(int fd[], int with_percents, int with_counts,
	       int with_areas, int with_labels, char *fmt)
{
    CELL **cell;
    int i;
    int row;
    double unit_area;
    int planimetric = 0;
    int compute_areas;
    double G_area_of_cell_at_row();


    cell = (CELL **) G_calloc(nfiles, sizeof(CELL *));
    for (i = 0; i < nfiles; i++)
	cell[i] = G_allocate_cell_buf();


    unit_area = 0.0;
    if (with_areas) {
	switch (G_begin_cell_area_calculations()) {
	case 0:
	case 1:
	    planimetric = 1;
	    unit_area = G_area_of_cell_at_row(0);
	    break;
	default:
	    planimetric = 0;
	    break;
	}
    }
    compute_areas = with_areas && !planimetric;


    initialize_cell_stats(nfiles);

    for (row = 0; row < nrows; row++) {
	if (compute_areas)
	    unit_area = G_area_of_cell_at_row(row);

	G_percent(row, nrows, 2);

	for (i = 0; i < nfiles; i++) {
	    if (G_get_c_raster_row(fd[i], cell[i], row) < 0)
		G_fatal_error(_("Unable to read raster <map %d of %d> row %d"),
				i+1, nfiles, row);


	    if(is_fp[i])
		fix_max_fp_val(cell[i], ncols);


	    reset_null_vals(cell[i], ncols);
	}

	update_cell_stats(cell, ncols, unit_area);
    }

    G_percent(row, nrows, 2);

    sort_cell_stats();
    print_cell_stats(fmt, with_percents, with_counts, with_areas, with_labels,
		     fs);

    return 0;
}
