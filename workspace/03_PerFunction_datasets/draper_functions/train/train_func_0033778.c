gsd_surf2real(geosurf * gs, Point3 point)
{
    if (gs) {
	point[X] += gs->ox;
	point[Y] += gs->oy;
    }

    return;
}
