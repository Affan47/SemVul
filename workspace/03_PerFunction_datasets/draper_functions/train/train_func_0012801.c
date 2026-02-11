interp_closest_dist_to_box( vec3d *hitpt, vec3d *p0, vec3d *min, vec3d *max )
{
	float *origin = (float *)&p0->xyz.x;
	float *minB = (float *)min;
	float *maxB = (float *)max;
	float *coord = (float *)&hitpt->xyz.x;
	int inside = 1;
	int i;

	for (i=0; i<3; i++ )	{
		if ( origin[i] < minB[i] )	{
			coord[i] = minB[i];
			inside = 0;
		} else if (origin[i] > maxB[i] )	{
			coord[i] = maxB[i];
			inside = 0;
		} else {
			coord[i] = origin[i];
		}
	}

	if ( inside )	{
		return 0.0f;
	}

	return vm_vec_dist(hitpt,p0);
}
