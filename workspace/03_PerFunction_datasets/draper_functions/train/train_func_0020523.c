N_alloc_gwflow_data3d(int cols, int rows, int depths,
				       int river, int drain)
{
    N_gwflow_data3d *data;

    data = (N_gwflow_data3d *) G_calloc(1, sizeof(N_gwflow_data3d));

    data->phead = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->phead_start = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->status = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->hc_x = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->hc_y = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->hc_z = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->q = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->s = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->nf = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    data->r = N_alloc_array_2d(cols, rows, 1, DCELL_TYPE);

    if (river) {
	data->river_head =
	    N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
	data->river_leak =
	    N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
	data->river_bed = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    }
    else {
	data->river_head = NULL;
	data->river_leak = NULL;
	data->river_bed = NULL;
    }

    if (drain) {
	data->drain_leak =
	    N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
	data->drain_bed = N_alloc_array_3d(cols, rows, depths, 1, DCELL_TYPE);
    }
    else {
	data->drain_leak = NULL;
	data->drain_bed = NULL;
    }

    return data;
}
