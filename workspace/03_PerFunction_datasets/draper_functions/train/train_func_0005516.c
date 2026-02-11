init_coordcnv(double exag, struct Cell_head *w, double min, double max)
{

    Yrange = (max - min) * exag;
    Zrange = (w->rows - 1) * w->ns_res;
    Xrange = (w->cols - 1) * w->ew_res;

    transX = -(G_col_to_easting(0.5, w));
    transZ = -(G_row_to_northing(0.5, w));
    transY = -min;

    if (Zrange >= Xrange && Zrange >= Yrange) {
	scaleXZ = 1.0 / Zrange;
	scaleY = exag * scaleXZ;
    }
    else if (Xrange >= Zrange && Xrange >= Yrange) {
	scaleXZ = 1.0 / Xrange;
	scaleY = exag * scaleXZ;
    }
    else
	scaleY = scaleXZ = 1.0 / Yrange;

    return 0;
}
