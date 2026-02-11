G_site_describe(struct Map_info *Map, int *dims, int *cat, int *strs,
		    int *dbls)
{
    if (Vect_is_3d(Map)) {
	G_debug(1, "Vector is 3D -> number of site dimensions is 3");
	*dims = 3;
    }
    else {
	G_debug(1, "Vector is 2D -> number of site dimensions is 2");
	*dims = 2;
    }

    *cat = CELL_TYPE;


    *dbls = Map->n_site_dbl;
    *strs = Map->n_site_str;

    return 0;
}
