N_init_geom_data_3d(G3D_Region * region3d, N_geom_data * geodata)
{
    N_geom_data *geom = geodata;
    struct Cell_head region2d;

#pragma omp critical
    {

	G_debug(2,
		"N_init_geom_data_3d: initializing the geometry structure");

	if (geom == NULL)
	    geom = N_alloc_geom_data();

	geom->dz = region3d->tb_res * G_database_units_to_meters_factor();
	geom->depths = region3d->depths;
	geom->dim = 3;


	G_get_set_window(&region2d);
	G3d_regionToCellHead(region3d, &region2d);
    }

    return N_init_geom_data_2d(&region2d, geom);
}
