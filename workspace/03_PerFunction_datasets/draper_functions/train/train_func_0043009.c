sort_polys_by_z()
{
    long *sortarray, i;
    p_polygon this;

    if (!polygons.end)
	return;

    sortarray = gp_alloc(sizeof(long) * polygons.end, "hidden sortarray");


    for (i = 0; i < polygons.end; i++)
	sortarray[i] = i;


    qsort(sortarray, (size_t) polygons.end, sizeof(long),
	  compare_polys_by_zmax);


#if HIDDEN3D_QUADTREE


    {
	int grid_x, grid_y;
	int grid_x_low, grid_x_high, grid_y_low, grid_y_high;

	for (grid_x = 0; grid_x < QUADTREE_GRANULARITY; grid_x++)
	    for (grid_y = 0; grid_y < QUADTREE_GRANULARITY; grid_y++)
		quadtree[grid_x][grid_y] = -1;

	for (i=polygons.end - 1; i >= 0; i--) {
	    this = plist + sortarray[i];

	    grid_x_low = coord_to_treecell(this->xmin);
	    grid_x_high = coord_to_treecell(this->xmax);
	    grid_y_low = coord_to_treecell(this->ymin);
	    grid_y_high = coord_to_treecell(this->ymax);

	    for (grid_x = grid_x_low; grid_x <= grid_x_high; grid_x++) {
		for (grid_y = grid_y_low; grid_y <= grid_y_high; grid_y++) {
		    p_qtreelist newhead = nextfrom_dynarray(&qtree);

		    newhead->next = quadtree[grid_x][grid_y];
		    newhead->p = sortarray[i];

		    quadtree[grid_x][grid_y] = newhead - qlist;
		}
	    }
	}
    }

#else
    this = plist + sortarray[0];
    for (i = 1; i < polygons.end; i++) {
	this->next = sortarray[i];
	this = plist + sortarray[i];
    }
    this->next = -1L;

#endif
    pfirst = sortarray[0];

    free(sortarray);
}
