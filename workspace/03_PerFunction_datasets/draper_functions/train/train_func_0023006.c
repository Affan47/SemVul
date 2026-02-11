fvi_ray_boundingbox( vec3d *min, vec3d *max, vec3d * p0, vec3d *pdir, vec3d *hitpt )
{
	bool inside = true;
	bool middle[3] = { true, true, true };
	int i;
	int which_plane;
	float maxt[3];
	float candidate_plane[3];

	for (i = 0; i < 3; i++) {
		if (p0->a1d[i] < min->a1d[i]) {
			candidate_plane[i] = min->a1d[i];
			middle[i] = false;
			inside = false;
		} else if (p0->a1d[i] > max->a1d[i]) {
			candidate_plane[i] = max->a1d[i];
			middle[i] = false;
			inside = false;
		}
	}


	if ( inside ) {
		*hitpt = *p0;
		return 1;
	}


	for (i = 0; i < 3; i++) {
		if ( !middle[i] && (pdir->a1d[i] != 0.0f) )
			maxt[i] = (candidate_plane[i] - p0->a1d[i]) / pdir->a1d[i];
		else
			maxt[i] = -1.0f;
	}


	which_plane = 0;
	for (i = 1; i < 3; i++) {
		if (maxt[which_plane] < maxt[i])
			which_plane = i;
	}


	if (maxt[which_plane] < 0.0f)
		return 0;

	for (i = 0; i < 3; i++) {
		if (which_plane != i) {
			hitpt->a1d[i] = p0->a1d[i] + maxt[which_plane] * pdir->a1d[i];

			if ( (hitpt->a1d[i] < min->a1d[i]) || (hitpt->a1d[i] > max->a1d[i]) )
				return 0;
		} else {
			hitpt->a1d[i] = candidate_plane[i];
		}
	}

	return 1;
}
