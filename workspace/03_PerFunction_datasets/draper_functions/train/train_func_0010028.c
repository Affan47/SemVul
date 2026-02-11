in_vregion(geosurf * gs, float *pt)
{
    if (pt[X] >= 0.0 && pt[Y] <= gs->yrange) {
	if (pt[X] <= VCOL2X(gs, VCOLS(gs))) {
	    return (pt[Y] >= VROW2Y(gs, VROWS(gs)));
	}
    }

    return (0);
}
