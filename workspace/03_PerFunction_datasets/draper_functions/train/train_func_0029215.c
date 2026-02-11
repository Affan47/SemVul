XY_intersect_plane(float *intersect, float *plane)
{
    float x, y;

    if (!plane[Z]) {
	return (0);
    }

    x = intersect[X];
    y = intersect[Y];
    intersect[Z] = (plane[X] * x + plane[Y] * y + plane[W]) / -plane[Z];

    return (1);
}
