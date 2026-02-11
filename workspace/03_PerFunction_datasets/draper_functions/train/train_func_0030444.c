trail_add_segment( trail *trailp, vec3d *pos )
{
	int next = trailp->tail;
	trailp->tail++;
	if ( trailp->tail >= NUM_TRAIL_SECTIONS )
		trailp->tail = 0;

	if ( trailp->head == trailp->tail )	{

		trailp->head++;
		if ( trailp->head >= NUM_TRAIL_SECTIONS )
			trailp->head = 0;
	}

	trailp->pos[next] = *pos;
	trailp->val[next] = 0.0f;
}
