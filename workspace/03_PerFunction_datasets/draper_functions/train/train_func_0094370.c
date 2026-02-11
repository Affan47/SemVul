trail_set_segment( trail *trailp, vec3d *pos )
{
	int next = trailp->tail-1;
	if ( next < 0 )	{
		next = NUM_TRAIL_SECTIONS-1;
	}

	trailp->pos[next] = *pos;
}
