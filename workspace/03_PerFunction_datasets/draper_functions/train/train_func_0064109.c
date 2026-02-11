wiggle_bolt(Lightning * bolt)
{
	int         i;

	wiggle_line(bolt->middle, BOLT_VERTICIES, bolt->wiggle_amount);
	bolt->end2.x += NRAND(bolt->wiggle_amount) - bolt->wiggle_amount / 2;
	bolt->end2.y += NRAND(bolt->wiggle_amount) - bolt->wiggle_amount / 2;

	for (i = 0; i < bolt->fork_number; i++) {
		wiggle_line(bolt->branch[i].ForkVerticies, bolt->branch[i].num_used,
			    bolt->wiggle_amount);
		bolt->branch[i].ForkVerticies[0].x = bolt->middle[bolt->forks_start[i]].x;
		bolt->branch[i].ForkVerticies[0].y = bolt->middle[bolt->forks_start[i]].y;
	}

	if (bolt->wiggle_amount > 1)
		bolt->wiggle_amount -= 1;
	else
		bolt->wiggle_amount = 0;
}
