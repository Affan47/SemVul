GVL_slice_get_pos(int id, int slice_id,
		      float *x1, float *x2, float *y1, float *y2, float *z1,
		      float *z2, int *dir)
{
    geovol *gvl;
    geovol_slice *slice;
    int cols, rows, depths;

    gvl = gvl_get_vol(id);

    if (!gvl)
	return (-1);

    slice = gvl_slice_get_slice(id, slice_id);

    if (!slice)
	return (-1);

    if (slice->dir == X) {
	cols = gvl->rows;
	rows = gvl->depths;
	depths = gvl->cols;
    }
    else if (slice->dir == Y) {
	cols = gvl->cols;
	rows = gvl->depths;
	depths = gvl->rows;
    }
    else if (slice->dir == Z) {
	cols = gvl->cols;
	rows = gvl->rows;
	depths = gvl->depths;
    }
    else {
	return (-1);
    }

    *x1 = slice->x1 / (cols - 1);
    *x2 = slice->x2 / (cols - 1);
    *y1 = slice->y1 / (rows - 1);
    *y2 = slice->y2 / (rows - 1);
    *z1 = slice->z1 / (depths - 1);
    *z2 = slice->z2 / (depths - 1);

    *dir = slice->dir;

    return (1);
}
