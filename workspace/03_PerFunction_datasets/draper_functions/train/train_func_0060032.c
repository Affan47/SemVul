Gs_loadmap_as_bitmap(struct Cell_head *wind, const char *map_name,
			 struct BM *buff)
{
    FILEDESC cellfile;
    const char *map_set;
    char *nullflags;
    int *tmp_buf;
    int row, col;

    G_debug(3, "Gs_loadmap_as_bitmap");

    map_set = G_find_cell2(map_name, "");
    if (!map_set) {
	G_warning(_("Raster map <%s> not found"), map_name);
	return -1;
    }

    if ((cellfile = G_open_cell_old(map_name, map_set)) == -1) {
	G_fatal_error(_("Unable to open raster map <%s>"), map_name);
    }

    tmp_buf = (int *)G_malloc(wind->cols * sizeof(int));
    if (!tmp_buf) {
	return -1;
    }

    nullflags = G_allocate_null_buf();
    if (!nullflags) {
	G_fatal_error(_("Unable to allocate memory for a null buffer"));
    }

    G_message(_("Loading raster map <%s>..."),
	      G_fully_qualified_name(map_name, map_set));

    for (row = 0; row < wind->rows; row++) {
	G_get_null_value_row(cellfile, nullflags, row);

	for (col = 0; col < wind->cols; col++) {
	    if (nullflags[col]) {

		BM_set(buff, col, row, 1);
	    }
	    else {
		BM_set(buff, col, row, 0);
	    }
	}
    }

    G_close_cell(cellfile);

    G_free(tmp_buf);
    G_free(nullflags);

    return (1);
}
