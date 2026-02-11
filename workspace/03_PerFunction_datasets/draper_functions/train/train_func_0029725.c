plot(int x, int y)
{
    char name[100], mapset[100];
    struct Cell_head cellhd;

    if (x > VIEW_MAP1->left && x < VIEW_MAP1->right) {
	if (!choose_groupfile(name, mapset))
	    return 1;
	if (G_get_cellhd(name, mapset, &cellhd) < 0)
	    return 1;

	Erase_view(VIEW_MAP1_ZOOM);
	VIEW_MAP1_ZOOM->cell.configured = 0;

	G_adjust_window_to_box(&cellhd, &VIEW_MAP1->cell.head,
			       VIEW_MAP1->nrows, VIEW_MAP1->ncols);
	Configure_view(VIEW_MAP1, name, mapset, cellhd.ns_res, cellhd.ew_res);
	drawcell(VIEW_MAP1, 0);
    }
    else if (x > VIEW_MAP2->left && x < VIEW_MAP2->right) {
	if (!choose_cellfile(name, mapset))
	    return 1;
	select_target_env();

	if (G_get_cellhd(name, mapset, &cellhd) < 0) {
	    select_current_env();
	    return 1;
	}

	Erase_view(VIEW_MAP2_ZOOM);
	VIEW_MAP2_ZOOM->cell.configured = 0;

	G_adjust_window_to_box(&cellhd, &VIEW_MAP2->cell.head,
			       VIEW_MAP2->nrows, VIEW_MAP2->ncols);
	Configure_view(VIEW_MAP2, name, mapset, cellhd.ns_res, cellhd.ew_res);
	select_target_env();
	drawcell(VIEW_MAP2, 0);
	select_current_env();
	if (from_screen < 0) {
	    from_flag = 1;
	    from_screen = 0;
	    if (from_keyboard < 0) {
		from_keyboard = 0;
		from_screen = 1;
	    }
	}
    }
    else
	return 0;

    display_points(1);
    return 1;
}
